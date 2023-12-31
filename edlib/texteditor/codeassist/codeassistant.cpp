/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

#include "codeassistant.h"
#include "basetexteditor.h"
#include "completionassistprovider.h"
#include "quickfixassistprovider.h"
#include "iassistprocessor.h"
#include "iassistproposal.h"
#include "iassistproposalwidget.h"
#include "iassistinterface.h"
#include "iassistproposalitem.h"
#include "runner.h"
#include "qtcassert.h"
//#include "Core.h"

#include <texteditor.h>
#include <texteditorsettings.h>
#include <completionsettings.h>
//#include <extensionsystem/pluginmanager.h>

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QTimer>
#include <QtCore/QDebug>
#include <QtGui/QKeyEvent>

using namespace TextEditor;
using namespace Internal;

namespace {

template <class T>
void filterEditorSpecificProviders(QList<T *> *providers, const Core::Context &context )
{
    typename QList<T *>::iterator it = providers->begin();
    while (it != providers->end()) {
        if ((*it)->supportsEditor(context))
            ++it;
        else
            it = providers->erase(it);
    }
}

} // Anonymous

namespace TextEditor {

class CodeAssistantPrivate : public QObject
{
    Q_OBJECT

public:
    CodeAssistantPrivate(CodeAssistant *assistant);
    virtual ~CodeAssistantPrivate();

    void configure(BaseTextEditor *textEditor);
    void reconfigure();
    bool isConfigured() const;

    void invoke(AssistKind kind, IAssistProvider *provider = 0);
    void process();
    void requestProposal(AssistReason reason, AssistKind kind, IAssistProvider *provider = 0);
    void cancelCurrentRequest();
    void invalidateCurrentRequestData();
    void displayProposal(IAssistProposal *newProposal, AssistReason reason);
    bool isDisplayingProposal() const;
    bool isWaitingForProposal() const;

    void notifyChange();
    bool hasContext() const;
    void destroyContext();

    CompletionAssistProvider *identifyActivationSequence();

    void stopAutomaticProposalTimer();
    void startAutomaticProposalTimer();

    virtual bool eventFilter(QObject *o, QEvent *e);

signals:
    void finished();

private slots:
    void finalizeRequest();
    void proposalComputed();
    void processProposalItem(IAssistProposalItem *proposalItem);
    void handlePrefixExpansion(const QString &newPrefix);
    void finalizeProposal();
    void automaticProposalTimeout();
    void updateCompletionSettings(const TextEditor::CompletionSettings &);
    void explicitlyAborted();
    void clearAbortedPosition();

private:
    CodeAssistant *m_q;
    BaseTextEditor *m_textEditor;
    CompletionAssistProvider *m_completionProvider;
    QList<QuickFixAssistProvider *> m_quickFixProviders;
    Internal::ProcessorRunner *m_requestRunner;
    IAssistProvider *m_requestProvider;
    AssistKind m_assistKind;
    IAssistProposalWidget *m_proposalWidget;
    QScopedPointer<IAssistProposal> m_proposal;
    bool m_receivedContentWhileWaiting;
    QTimer m_automaticProposalTimer;
//    CompletionSettings m_settings;
    int m_abortedBasePosition;
    static const QChar m_null;
};

} // TextEditor

// --------------------
// CodeAssistantPrivate
// --------------------
const QChar CodeAssistantPrivate::m_null;

static const int AutomaticProposalTimerInterval = 400;

CodeAssistantPrivate::CodeAssistantPrivate(CodeAssistant *assistant)
    : m_q(assistant)
    , m_textEditor(0)
    , m_completionProvider(0)
    , m_requestRunner(0)
    , m_requestProvider(0)
    , m_assistKind(TextEditor::Completion)
    , m_proposalWidget(0)
    , m_receivedContentWhileWaiting(false)
//    , m_settings(TextEditorSettings::completionSettings())
    , m_abortedBasePosition(-1)
{
    m_automaticProposalTimer.setSingleShot(true);
    m_automaticProposalTimer.setInterval(AutomaticProposalTimerInterval);
    connect(&m_automaticProposalTimer, SIGNAL(timeout()), this, SLOT(automaticProposalTimeout()));

//    connect(TextEditorSettings::instance(),
//            SIGNAL(completionSettingsChanged(TextEditor::CompletionSettings)),
//            this,
//            SLOT(updateCompletionSettings(TextEditor::CompletionSettings)));
}

CodeAssistantPrivate::~CodeAssistantPrivate()
{
}

void CodeAssistantPrivate::configure(BaseTextEditor *textEditor)
{
    // @TODO: There's a list of providers but currently only the first one is used. Perhaps we
    // should implement a truly mechanism to support multiple providers for an editor (either
    // merging or not proposals) or just leave it as not extensible and store directly the one
    // completion and quick-fix provider (getting rid of the list).

    m_textEditor = textEditor;
    if ( CompletionAssistProvider *provider = m_textEditor->completionProvider() )
        m_completionProvider = provider;
    else {
//        QList<CompletionAssistProvider *> completionProviders;
//        completionProviders = Core::Storage::mainWindow()->getCompletionAssistProviders();
//        filterEditorSpecificProviders(&completionProviders, m_textEditor->context());
//        if ( !completionProviders.isEmpty() )
//            m_completionProvider = completionProviders[0];
    }

//    m_quickFixProviders =
//        ExtensionSystem::PluginManager::getObjects<QuickFixAssistProvider>();
//    filterEditorSpecificProviders(&m_quickFixProviders, m_textEditor->document()->id());

    m_textEditor->editorWidget()->installEventFilter(this);
//    connect(m_textEditor->baseTextDocument(),SIGNAL(mimeTypeChanged()),
//            m_q, SLOT(reconfigure()));
    }

void CodeAssistantPrivate::reconfigure()
{
    if (isConfigured())
        m_completionProvider = m_textEditor->completionProvider();
}

bool CodeAssistantPrivate::isConfigured() const
{
    return m_textEditor != 0;
}

void CodeAssistantPrivate::invoke(AssistKind kind, IAssistProvider *provider)
{
    if (!isConfigured())
        return;

    stopAutomaticProposalTimer();

    if (isDisplayingProposal() && m_assistKind == kind && !m_proposal->isFragile()) {
        m_proposalWidget->setReason(ExplicitlyInvoked);
        m_proposalWidget->updateProposal(
                    m_textEditor->textAt(
                        m_proposal->basePosition(),
                                 m_textEditor->position() - m_proposal->basePosition()));
    } else {
        destroyContext();
        requestProposal(ExplicitlyInvoked, kind, provider);
    }
}

void CodeAssistantPrivate::process()
{
    if (!isConfigured())
        return;

    stopAutomaticProposalTimer();

    if (m_assistKind == TextEditor::Completion) {
        if (/*m_settings.m_completionTrigger != ManualCompletion*/ true) {
            if (CompletionAssistProvider *provider = identifyActivationSequence()) {
                if (isWaitingForProposal())
                    cancelCurrentRequest();
                requestProposal(ActivationCharacter, Completion, provider);
                return;
            }
        }

        startAutomaticProposalTimer();
    } else {
        m_assistKind = TextEditor::Completion;
    }
}

void CodeAssistantPrivate::requestProposal(AssistReason reason,
                                           AssistKind kind,
                                           IAssistProvider *provider)
{
    QTC_ASSERT(!isWaitingForProposal(), return);

    if (m_textEditor->hasBlockSelection())
        return; // TODO

    if (!provider) {
        if (kind == Completion)
            provider = m_completionProvider;
        else if (!m_quickFixProviders.isEmpty())
            provider = m_quickFixProviders.at(0);

        if (!provider)
            return;
    }

    m_assistKind = kind;
    IAssistProcessor *processor = provider->createProcessor();
    IAssistInterface *assistInterface =
        m_textEditor->createAssistInterface(kind, reason);
    if (!assistInterface)
        return;

    if (provider->isAsynchronous()) {
        if (IAssistProposal *newProposal = processor->immediateProposal(assistInterface))
            displayProposal(newProposal, reason);
        else
            destroyContext();

        m_requestProvider = provider;
        m_requestRunner = new ProcessorRunner;
        connect(m_requestRunner, SIGNAL(finished()), this, SLOT(proposalComputed()));
        connect(m_requestRunner, SIGNAL(finished()), this, SLOT(finalizeRequest()));
        connect(m_requestRunner, SIGNAL(finished()), this, SIGNAL(finished()));
        assistInterface->prepareForAsyncUse();
        m_requestRunner->setReason(reason);
        m_requestRunner->setProcessor(processor);
        m_requestRunner->setAssistInterface(assistInterface);
        m_requestRunner->start();
        return;
    }

    if (IAssistProposal *newProposal = processor->perform(assistInterface))
        displayProposal(newProposal, reason);
    delete processor;
}

void CodeAssistantPrivate::cancelCurrentRequest()
{
    m_requestRunner->setDiscardProposal(true);
    disconnect(m_requestRunner, SIGNAL(finished()), this, SLOT(proposalComputed()));
    invalidateCurrentRequestData();
}

void CodeAssistantPrivate::proposalComputed()
{
    // Since the request runner is a different thread, there's still a gap in which the queued
    // signal could be processed after an invalidation of the current request.
    if (m_requestRunner != sender())
        return;

    IAssistProposal *newProposal = m_requestRunner->proposal();
    AssistReason reason = m_requestRunner->reason();
    invalidateCurrentRequestData();
    displayProposal(newProposal, reason);
}

void CodeAssistantPrivate::displayProposal(IAssistProposal *newProposal, AssistReason reason)
{
    if (!newProposal)
        return;

    QScopedPointer<IAssistProposal> proposalCandidate(newProposal);

    if (isDisplayingProposal()) {
        if (!m_proposal->isFragile())
            return;
        destroyContext();
    }

    int basePosition = proposalCandidate->basePosition();
    if (m_textEditor->position() < basePosition)
        return;

    /// NOTE: does is it need?!
//    if (m_abortedBasePosition == basePosition && reason != ExplicitlyInvoked)
//        return;

    clearAbortedPosition();
    m_proposal.reset(proposalCandidate.take());

    if (m_proposal->isCorrective())
        m_proposal->makeCorrection(m_textEditor);

    basePosition = m_proposal->basePosition();
    m_proposalWidget = m_proposal->createWidget();
    connect(m_proposalWidget, SIGNAL(destroyed()), this, SLOT(finalizeProposal()));
    connect(m_proposalWidget, SIGNAL(prefixExpanded(QString)),
            this, SLOT(handlePrefixExpansion(QString)));
    connect(m_proposalWidget, SIGNAL(proposalItemActivated(IAssistProposalItem*)),
            this, SLOT(processProposalItem(IAssistProposalItem*)));
    connect(m_proposalWidget, SIGNAL(explicitlyAborted()),
            this, SLOT(explicitlyAborted()));
    m_proposalWidget->setAssistant(m_q);
    m_proposalWidget->setReason(reason);
    m_proposalWidget->setKind(m_assistKind);
    m_proposalWidget->setUnderlyingWidget(m_textEditor->editorWidget());
    m_proposalWidget->setModel(m_proposal->model());
    m_proposalWidget->setDisplayRect(m_textEditor->cursorRect(basePosition));
    if (m_receivedContentWhileWaiting)
        m_proposalWidget->setIsSynchronized(false);
    else
        m_proposalWidget->setIsSynchronized(true);
    m_proposalWidget->showProposal(m_textEditor->textAt(
                                       basePosition,
                                       m_textEditor->position() - basePosition));
}

void CodeAssistantPrivate::processProposalItem(IAssistProposalItem *proposalItem)
{
    QTC_ASSERT(m_proposal, return);
    proposalItem->apply(m_textEditor, m_proposal->basePosition());
    destroyContext();
    process();
}

void CodeAssistantPrivate::handlePrefixExpansion(const QString &newPrefix)
{
    QTC_ASSERT(m_proposal, return);
    const int currentPosition = m_textEditor->position();
    m_textEditor->setCursorPosition(m_proposal->basePosition());
    m_textEditor->replace(currentPosition - m_proposal->basePosition(), newPrefix);
    notifyChange();
}

void CodeAssistantPrivate::finalizeRequest()
{
    if (ProcessorRunner *runner = qobject_cast<ProcessorRunner *>(sender()))
        delete runner;
}

void CodeAssistantPrivate::finalizeProposal()
{
    stopAutomaticProposalTimer();
    m_proposal.reset();
    m_proposalWidget = 0;
    if (m_receivedContentWhileWaiting)
        m_receivedContentWhileWaiting = false;
}

bool CodeAssistantPrivate::isDisplayingProposal() const
{
    return m_proposalWidget != 0;
}

bool CodeAssistantPrivate::isWaitingForProposal() const
{
    return m_requestRunner != 0;
}

void CodeAssistantPrivate::invalidateCurrentRequestData()
{
    m_requestRunner = 0;
    m_requestProvider = 0;
}

CompletionAssistProvider *CodeAssistantPrivate::identifyActivationSequence()
{
    if (!m_completionProvider)
        return 0;

    const int length = m_completionProvider->activationCharSequenceLength();
        if (length == 0)
        return 0;
    QString sequence = m_textEditor->textAt(m_textEditor->position() - length,
                                                            length);
        // In pretty much all cases the sequence will have the appropriate length. Only in the
        // case of typing the very first characters in the document for providers that request a
        // length greater than 1 (currently only C++, which specifies 3), the sequence needs to
    // be prepended so it has the expected length.
        const int lengthDiff = length - sequence.length();
        for (int j = 0; j < lengthDiff; ++j)
            sequence.prepend(m_null);
    return m_completionProvider->isActivationCharSequence(sequence) ? m_completionProvider : 0;
}

void CodeAssistantPrivate::notifyChange()
{
    stopAutomaticProposalTimer();

    if (isDisplayingProposal()) {
        QTC_ASSERT(m_proposal, return);
        if (m_textEditor->position() < m_proposal->basePosition()) {
            destroyContext();
        } else {
            m_proposalWidget->updateProposal(
                m_textEditor->textAt(m_proposal->basePosition(),
                                     m_textEditor->position() - m_proposal->basePosition()));
            if (m_proposal->isFragile())
                startAutomaticProposalTimer();
        }
    }
}

bool CodeAssistantPrivate::hasContext() const
{
    return m_requestRunner || m_proposalWidget;
}

void CodeAssistantPrivate::destroyContext()
{
    stopAutomaticProposalTimer();

    if (isWaitingForProposal()) {
        cancelCurrentRequest();
    } else if (isDisplayingProposal()) {
        m_proposalWidget->closeProposal();
        disconnect(m_proposalWidget, SIGNAL(destroyed()), this, SLOT(finalizeProposal()));
        finalizeProposal();
    }
}

void CodeAssistantPrivate::startAutomaticProposalTimer()
{
    if (/*m_settings.m_completionTrigger == AutomaticCompletion*/ true)
        m_automaticProposalTimer.start();
}

void CodeAssistantPrivate::automaticProposalTimeout()
{
    if (isWaitingForProposal() || (isDisplayingProposal() && !m_proposal->isFragile()))
        return;

    requestProposal(IdleEditor, Completion);
}

void CodeAssistantPrivate::stopAutomaticProposalTimer()
{
    if (m_automaticProposalTimer.isActive())
        m_automaticProposalTimer.stop();
}

void CodeAssistantPrivate::updateCompletionSettings(const TextEditor::CompletionSettings & /*settings*/)
{
//    m_settings = settings;
}

void CodeAssistantPrivate::explicitlyAborted()
{
    QTC_ASSERT(m_proposal, return);
    m_abortedBasePosition = m_proposal->basePosition();
}

void CodeAssistantPrivate::clearAbortedPosition()
{
    m_abortedBasePosition = -1;
}

bool CodeAssistantPrivate::eventFilter(QObject *o, QEvent *e)
{
    Q_UNUSED(o);

    if (isWaitingForProposal()) {
        QEvent::Type type = e->type();
        if (type == QEvent::FocusOut) {
            destroyContext();
        } else if (type == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
            const QString &keyText = keyEvent->text();

            CompletionAssistProvider *completionProvider = 0;
            if ((keyText.isEmpty()
                 && keyEvent->key() != Qt::LeftArrow
                 && keyEvent->key() != Qt::RightArrow
                 && keyEvent->key() != Qt::Key_Shift)
                || (!keyText.isEmpty()
                    && (((completionProvider = dynamic_cast<CompletionAssistProvider *>(m_requestProvider))
                            ? !completionProvider->isContinuationChar(keyText.at(0))
                            : false)))) {
                destroyContext();
            } else if (!keyText.isEmpty() && !m_receivedContentWhileWaiting) {
                m_receivedContentWhileWaiting = true;
            }
        }
    }

    return false;
}

// -------------
// CodeAssistant
// -------------
CodeAssistant::CodeAssistant() : d(new CodeAssistantPrivate(this))
{
    connect(d, SIGNAL(finished()), SIGNAL(finished()));
}

CodeAssistant::~CodeAssistant()
{
    delete d;
}

void CodeAssistant::configure(BaseTextEditor *textEditor)
{
    d->configure(textEditor);
}

void CodeAssistant::process()
{
    d->process();
}

void CodeAssistant::notifyChange()
{
    d->notifyChange();
}

bool CodeAssistant::hasContext() const
{
    return d->hasContext();
}

void CodeAssistant::destroyContext()
{
    d->destroyContext();
}

void CodeAssistant::invoke(AssistKind kind, IAssistProvider *provider)
{
    d->invoke(kind, provider);
}

void CodeAssistant::reconfigure()
{
    d->reconfigure();
}

#include "codeassistant.moc"
