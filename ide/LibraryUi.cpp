#include "MainWindow.h"
#include "BuildController.h"
#include "DebugController.h"
#include "EditorDocument.h"
#include "LibrariesDialog.h"
#include "LibraryResolver.h"
#include "FileBuildOptions.h"
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QSaveFile>
#include <QVBoxLayout>

void MainWindow::configureLibraries()
{
    for (auto* resolver : findChildren<LibraryResolver*>()) {
        resolver->chooseProvider = [this](const QString& module, const QStringList& providers) {
            bool ok = false;
            const QString choice = QInputDialog::getItem(this, "Choose Library Package", "Package providing " + module + ":", providers, 0, false, &ok);
            return ok ? choice : QString();
        };
        resolver->confirmInstall = [this](const QStringList& packages) {
            return QMessageBox::question(this, "Install Libraries", "This build needs:\n\n" + packages.join('\n') + "\n\nInstall these packages and their dependencies?", QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Yes) == QMessageBox::Yes;
        };
        connect(resolver, &LibraryResolver::output, this, [this](const QString& text) {
            if (!libraryConsole_) {
                auto* dialog = new QDialog(this); dialog->setWindowTitle("Library Console"); dialog->resize(800, 440);
                auto* layout = new QVBoxLayout(dialog); auto* console = new QPlainTextEdit; console->setReadOnly(true); console->setObjectName("libraryConsole"); layout->addWidget(console);
                auto* buttons = new QDialogButtonBox(QDialogButtonBox::Close);
                layout->addWidget(buttons);
                connect(buttons, &QDialogButtonBox::rejected, dialog, &QDialog::close);
                dialog->setAttribute(Qt::WA_DeleteOnClose); libraryConsole_ = console; dialog->show();
            }
            libraryConsole_->moveCursor(QTextCursor::End); libraryConsole_->insertPlainText(text);
        });
    }
}
void MainWindow::editLibraries()
{
    if (build_->isBusy() || debug_->isBusy()) return;
    auto* document = currentDocument();
    const bool project = !project_.root.isEmpty();
    FileBuildOptions options; QString error; ProjectFolder loaded;
    if (project) {
        // Save an open settings tab first, so the dialog never overwrites an unsaved edit.
        auto* config = findOpenDocument(project_.absolute("small.project"));
        if (config && !maybeSave(config)) return;
        if (!loaded.load(project_.root, &error)) { QMessageBox::warning(this, "Libraries", error); return; }
    } else {
        if (!document || document->isReadOnly()) return;
        const QString directory = document->filePath().isEmpty() ? documentsDirectory() : QFileInfo(document->filePath()).absolutePath();
        if (!FileBuildOptions::parse(document->toPlainText(), directory, &options, &error)) { QMessageBox::warning(this, "Libraries", error); return; }
    }
    LibrariesDialog dialog(project ? loaded.libraries : options.libraries, this);
    dialog.setWindowTitle("Libraries — " + (project ? loaded.name : document->displayName()));
    applyStyleSheetTo(&dialog);
    if (dialog.exec() != QDialog::Accepted) return;
    if (project) {
        auto settings = loaded.settings; settings.insert("libraries", QJsonArray::fromStringList(dialog.libraries()));
        const auto bytes = QJsonDocument(settings).toJson(); QSaveFile file(loaded.absolute("small.project"));
        if (!file.open(QIODevice::WriteOnly) || file.write(bytes) != bytes.size() || !file.commit()) { QMessageBox::warning(this, "Libraries", "Cannot save small.project."); return; }
        if (auto* config = findOpenDocument(file.fileName())) { config->setPlainText(QString::fromUtf8(bytes)); config->document()->setModified(false); }
        refreshProject();
    } else {
        KTextEditor::Document::EditingTransaction transaction(document->document());
        const QString next = FileBuildOptions::withLibraries(document->toPlainText(), options, dialog.libraries());
        // Replace only the metadata; preserve code, cursor marks and normal undo behavior.
        const int count = options.lines;
        if (count) {
            const int end = qMin(count, document->document()->lines() - 1);
            document->document()->removeText(KTextEditor::Range(0, 0, end, count < document->document()->lines() ? 0 : document->document()->lineLength(end)));
        }
        const QStringList lines = next.split('\n');
        int prefix = 0; while (prefix < lines.size() && lines[prefix].startsWith("//@")) ++prefix;
        document->document()->insertText({0, 0}, lines.mid(0, prefix).join('\n') + "\n");
    }
}
