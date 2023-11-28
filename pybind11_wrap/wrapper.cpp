#include "pybind11/pybind11.h"

#include "edlib.h"
#include "pythoneditor/pythoneditorwidget.h"
#include "cppeditor/cppeditor.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(pybed, m)
{
    m.doc() = ("Публичное АПИ библиотеки...");

    py::class_<PythonEditor::EditorWidget, QPlainTextEdit> (m, "PythonEditorWidget")
            .def("show", &PythonEditor::EditorWidget::show);

    py::class_<EditorsManager, std::unique_ptr<EditorsManager, py::nodelete>> (m, "EditorsManager")
            .def_static("createPythonEditor", &EditorsManager::createPythonEditor)
            .def_static("createCppEditor", &EditorsManager::createCppEditor)
            ;
}
