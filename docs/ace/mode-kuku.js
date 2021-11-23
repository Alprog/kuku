define("ace/mode/kuku_highlight_rules",["require","exports","module","ace/lib/oop","ace/mode/text_highlight_rules"], function(require, exports, module) {
"use strict";

var oop = require("../lib/oop");
var TextHighlightRules = require("./text_highlight_rules").TextHighlightRules;

var KukuHighlightRules = function() {
    var keywordMapper = this.createKeywordMapper({
        "constant.language.boolean": "true|false"
    }, "identifier");

    var identifierRe = "[a-zA-Z\\$_\u00a1-\uffff][a-zA-Z\\d\\$_\u00a1-\uffff]*\\b";

    this.$rules = {
        start: [{
            token: "keyword.other.kuku",
            regex: /\b(?:var|function|if|while|for|return)\b/
        }, {
            token: "string.quoted.single.kuku",
            regex: /R'/,
            push: [{
                token: "string.quoted.single.kuku",
                regex: /'/,
                next: "pop"
            }, {
                defaultToken: "string.quoted.single.kuku"
            }]
        }, {
            token: "string.quoted.double.kuku",
            regex: /R"/,
            push: [{
                token: "string.quoted.double.kuku",
                regex: /"/,
                next: "pop"
            }, {
                defaultToken: "string.quoted.double.kuku"
            }]
        }, {
            token: "string.quoted.other.kuku",
            regex: /R`/,
            push: [{
                token: "string.quoted.other.kuku",
                regex: /`/,
                next: "pop"
            }, {
                defaultToken: "string.quoted.other.kuku"
            }]
        }, {
            token: "string.quoted.single.kuku",
            regex: /'/,
            push: [{
                token: "string.quoted.single.kuku",
                regex: /'|$/,
                next: "pop"
            }, {
                token: "constant.character.escape.kuku",
                regex: /\\./
            }, {
                defaultToken: "string.quoted.single.kuku"
            }]
        }, {
            token: "string.quoted.double.kuku",
            regex: /"/,
            push: [{
                token: "string.quoted.double.kuku",
                regex: /"|$/,
                next: "pop"
            }, {
                token: "constant.character.escape.kuku",
                regex: /\\./
            }, {
                defaultToken: "string.quoted.double.kuku"
            }]
        }, {
            token: "string.quoted.other.kuku",
            regex: /`/,
            push: [{
                token: "string.quoted.other.kuku",
                regex: /`|$/,
                next: "pop"
            }, {
                token: "constant.character.escape.kuku",
                regex: /\\./
            }, {
                defaultToken: "string.quoted.other.kuku"
            }]
        }, {
            include: "#multicomment"
        }, {
            token: "comment.line.other.kuku",
            regex: /#.*$/
        }, {
            token: "comment.block.other.kuku",
            regex: /\*\//,
            push: [{
                token: "comment.block.other.kuku",
                regex: /\/\*/,
                next: "pop"
            }, {
                defaultToken: "comment.block.other.kuku"
            }]
        }, {
            token: "comment.line.other.kuku",
            regex: /\/\*.*$/
        }],
        "#multicomment": [{
            token: "comment.block.other.kuku",
            regex: /#\[/,
            push: [{
                token: "comment.block.other.kuku",
                regex: /#\]/,
                next: "pop"
            }, {
                include: "#multicomment"
            }, {
                defaultToken: "comment.block.other.kuku"
            }]
        }]
    };
	
	this.normalizeRules();
};

oop.inherits(KukuHighlightRules, TextHighlightRules);

exports.KukuHighlightRules = KukuHighlightRules;
});



define("ace/mode/kuku",["require","exports","module","ace/lib/oop","ace/mode/text","ace/mode/kuku_highlight_rules","ace/mode/folding/ini"], function(require, exports, module) {
"use strict";

var oop = require("../lib/oop");
var TextMode = require("./text").Mode;
var KukuHighlightRules = require("./kuku_highlight_rules").KukuHighlightRules;

var Mode = function() {
    this.HighlightRules = KukuHighlightRules;
    this.$behaviour = this.$defaultBehaviour;
};
oop.inherits(Mode, TextMode);

(function() {
    this.$id = "ace/mode/kuku";
}).call(Mode.prototype);

exports.Mode = Mode;
});            
