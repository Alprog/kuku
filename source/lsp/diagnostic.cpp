
#include "diagnostic.h"

lsp::diagnostic::diagnostic(lsp::range range, diagnostic_severity severity, int code, std::string message)
	: range {range}
	, severity {severity}
	, code {code}
	, message {message}
{
}