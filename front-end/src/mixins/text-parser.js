function isEscapeCharacter(ch){
    return typeof ch === "string" && ch.length === 1
           && (ch == " " || ch == "\b" || ch == "\f" || ch == "\n" || ch == "\r" || ch == "*" ||
               ch == "\t" || ch == "\v" || ch == "\0" || ch == "{" || ch == "}" || ch == "'" || ch == "\"");
}

function isOperatorString(str){
    return typeof str === "string"
           && (str == "F" || str == "G" || str == "U" || str == "!" || str == "|" || str == "&" || str == "=>" ||
               str == ">" || str == "<" || str == ">=" || str == "<=" || str == "==" || str == "!=" || str == "run" || str == "exec")
}

function isDefaultString(str) {
    return typeof str === "string"
           && (str == "const" || str == "proposition" || str == "property")
}

function defaultStringHighlight(str,is_editable){
    if(is_editable){
        return "<span style='color:#3376a8;' contenteditable=''>"+str+"</span>"
    }else{
        return"<span style='color:#3376a8;' >"+str+"</span>"
    }    
}

function operandHighlight(str,is_editable){
    if(is_editable){
        return "<span style='color:#404447;' contenteditable=''>"+str+"</span>"
    }else{
        return "<span style='color:#404447;' >"+str+"</span>"
    }
}

function operatorHighLight(str,is_editable){
    if(is_editable){
        return "<span style='color:#78953f;' contenteditable=''>"+str+"</span>"
    }else{
        return "<span style='color:#78953f;' >"+str+"</span>"
    }
}

function singleSelectionHighLight(str,spec,is_editable){
    let type = ""
    if(spec[0] == "."){
        type = spec.substring(1,spec.length)
    }
    if(!(type == "var" || type == "func" || type == "arg")){
        type = ""
    }
    let name = str.substring(1,str.length-1)
    
    if(is_editable){
        return "<a class='select-variable " + name + "-var' style='color:#c47635; cursor: pointer;' contenteditable='' type='"+type+"'>"+str+"</a>" + "<span style='color:#d2416e;' contenteditable=''>"+spec+"</span>"
    }else{
        return "<a class='select-variable " + name + "-var' style='color:#c47635; cursor: pointer;' contenteditable='' type='"+type+"'>"+str+"</a>" + "<span style='color:#d2416e;' >"+spec+"</span>"
    }
    
}

function nonamePropositionHighLight(str,is_editable){
    if(is_editable){
        return "<span style='color:#2a6fa3;' contenteditable=''>"+str+"</span>"
    }else{
        return "<span style='color:#2a6fa3;' >"+str+"</span>"
    }
}

function commentHighlight(str,is_editable){
    if(is_editable){
        return "<span style='color:#6e7781;' contenteditable=''>"+str+"</span>"
    }else{
        return "<span style='color:#6e7781;' >"+str+"</span>"
    }
}

function handleSingleStatement(opb, is_editable){
    let result = ""
    for(let op_id = 0; op_id < opb.length; op_id++){
        let op = opb[op_id]

        if(op[0] == "*"){
            result += commentHighlight(op, is_editable)
        }else if(isDefaultString(op, is_editable)){
            result += defaultStringHighlight(op, is_editable)
        }else if(isOperatorString(op)){
            result += operatorHighLight(op, is_editable)
        }else if(op[0] == "'"){
            let value = ""
            let spec = ""
            let p = op.split(op[0])
            if(p.length == 3 && p[2].length > 0){
                spec = p[2]
            }
            if(p.length == 3){
                value = "'" + p[1] + "'"
            }else if(p.length == 2){
                value = "'" + p[1]
            }
            result += singleSelectionHighLight(value,spec,is_editable)
        }else if(op[0] == "{"){
            result += nonamePropositionHighLight(op,is_editable)
        }else{
            result += operandHighlight(op,is_editable)
        }
    }
    return result
}

function handleTextSingleStatement(opb, is_editable){
    let result = ""
    for(let op_id = 0; op_id < opb.length; op_id++){
        let op = opb[op_id]

        if(op[0] == "*"){
            result += commentHighlight(op,is_editable)
        }else if(op[0] == "'"){
            let value = ""
            let spec = ""
            let p = op.split(op[0])
            if(p.length == 3 && p[2].length > 0){
                spec = p[2]
            }
            if(p.length == 3){
                value = "'" + p[1] + "'"
            }else if(p.length == 2){
                value = "'" + p[1]
            }
            result += singleSelectionHighLight(value,spec,is_editable)
        }else{
            result += operandHighlight(op,is_editable)
        }
    }
    return result
}

function extractLtlTag(code){
    let tokens = []
    let lines = code.split("\n")
    for(let line_id = 0; line_id < lines.length; line_id++){
        let line = lines[line_id]
        let opb = []
        let op = ""
        for(let i=0; i<line.length;){
            if(isEscapeCharacter(line[i]) || line[i] == "(" || line[i] == ")"){
                if(op.length > 0){
                    opb.push(op)  
                    op = ""
                }
                
                if(line[i] == "*"){
                    op += line[i]
                    i++
                    while(line[i] != "*" && i < line.length){
                        op += line[i]
                        i++
                    }
                    if(i < line.length){
                        op += line[i]
                    }
                    opb.push(op)
                    op = ""
                }else if(line[i] == "'" || line[i] == "\""){
                    let mark = line[i]
                    op = line[i]
                    i++
                    while(line[i] != mark && i < line.length){
                        op += line[i]
                        i++
                    }
                    if(i < line.length){
                        op += line[i]
                        if(line[i+1] != "."){
                            opb.push(op)
                            op = ""
                        }
                    }else{
                        opb.push(op)
                        op = ""
                    }
                }else if(line[i] == "{"){
                    op = line[i]
                    i++
                    while(line[i] != "}" && i < line.length){
                        op += line[i]
                        i++
                    }
                    if(i < line.length){
                        op += line[i]
                    }
                    opb.push(op)
                    op = ""
                }else{
                    opb.push(line[i])
                }
            }else{
                op += line[i]
            }
            i++
        }   
        if(op.length > 0){
            opb.push(op)
        }
        tokens.push(opb)
    }
    return tokens
}

export function acceptedInputKey(ch){
    return typeof ch === "string" && ch.length == 1 &&
        ((ch <= "9" && ch >= "0") || (ch <= "z" && ch >= "a") || (ch <= "Z" && ch >= "A") ||
          ch == "~" || ch == ">" || ch == "=" || ch == "<" || ch == "(" || ch == ")" || ch == "{" ||
          ch == "}" || ch == "'" || ch == "\"" || ch == "!" || ch == "|" || ch == "&" || ch == ":" || 
          ch == " " || ch == ";" || ch == "_")
}


export function analyseLTLCode(code, is_editable = true) {
    let result = ""

    let tokens = extractLtlTag(code)
    for(let i = 0; i <tokens.length; i++){
        let token = tokens[i]
        result += handleSingleStatement(token, is_editable)
        if(i < tokens.length - 1){
            result += "\n"
        }
    }

    return result
}

export function analyseLTLTextCode(code, is_editable = true) {
    let result = ""

    let tokens = extractLtlTag(code)
    for(let i = 0; i <tokens.length; i++){
        let token = tokens[i]
        result += handleTextSingleStatement(token,is_editable)
        if(i < tokens.length - 1){
            result += "\n"
        }
    }

    return result
}