#include <iostream>
#include "error_reporter.h"
#include "highlight_manager.h"
using namespace std;

ErrorReporter::ErrorReporter(HighlightManager &highlight_manager) {
    this->highlight_manager = &highlight_manager;
}

void ErrorReporter::log(ErrorType type, const std::string& message, const Location& location, const string &line) {
    string highlighted_line = highlight_manager->highlight(line, location);
    string full_message = message + ": \n" + highlighted_line;
    diagnostics.push_back({type, full_message, location});
}

void ErrorReporter::log(ErrorType type, const string& message, const Location& location) {
    diagnostics.push_back({type, message, location});
}

bool ErrorReporter::has_errors() const {
    return !diagnostics.empty();
}

void ErrorReporter::display_errors() const {
    if (!has_errors()) {
        return;
    }
    cout << endl;
    cout << "=== Error Report (" << diagnostics.size() << " errors) ===" << endl;
    for (const auto& diag : diagnostics) {
        cout << diag.to_string() << endl << endl;
    }
}

void ErrorReporter::clear_errors() {
    diagnostics.clear();
}