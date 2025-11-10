#include <iostream>
#include "error_reporter.h"
using namespace std;

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