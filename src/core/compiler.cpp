#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "compiler.h"
#include "file_operations.h"
#include "script_line.h"
#include "memory.h"
#include "expression.h"
#include "token.h"
#include "syntax_validator.h"
#include "tokenizer.h"
#include "error_reporter.h"
#include "exceptions.h"
#include "comment_remover.h"
#include "highlight_manager.h"
using namespace std;

Compiler::Compiler() {
    memory = new Memory();
    comment_remover = new CommentRemover();
    tokenizer = new Tokenizer();
    error_reporter = new ErrorReporter();
    highlight_manager = new HighlightManager();
    syntax_validator = new SyntaxValidator(*error_reporter, *highlight_manager);
}

string Compiler::compile_and_run(string path) {
    compile_file(path);
    if (error_reporter->has_errors()) {
        error_reporter->display_errors();
        return "Compilation failed due to errors.";
    }
    return run_file();
    if (error_reporter->has_errors()) {
        error_reporter->display_errors();
        return "Runtime failed due to errors.";
    }
}

void Compiler::compile_file(string path) {
    vector<string> input = read_file(path);
    input = comment_remover->remove_multiline_comment(input);
    for (int i=0; i < input.size(); i++) {
        Location * location = new Location(path, i+1, 1);
        ScriptLine * script_line = new ScriptLine(*location, input[i]);
        script_line->remove_comments(*comment_remover);
        if (script_line->is_empty())
            continue;
        script_line->compile(*comment_remover, *tokenizer, *syntax_validator);
        script_lines.push_back(*script_line);
    } 
}

string Compiler::run_file() {
    string output = "";
    for (auto& script_line : script_lines) {
        try {
            script_line.run(*memory);
        } catch (const Error& e) {
            error_reporter->log(ErrorType::Syntax, e.what(), script_line.get_location());
        }
    }
    return output;
}