
#include "diagnostic.h"

lsp::diagnostic::diagnostic(lsp::range range, diagnostic_severity severity, int code, std::u16string message)
	: range {range}
	, severity {severity}
	, code {code}
	, message {message}
{
}