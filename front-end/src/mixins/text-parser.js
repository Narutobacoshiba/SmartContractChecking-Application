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

function defaultStringHighlight(str){
    return "<span style='color:#3376a8;' contenteditable=''>"+str+"</span>"
}

function operandHighlight(str){
    return "<span style='color:#404447;' contenteditable=''>"+str+"</span>"
}

function operatorHighLight(str){
    return "<span style='color:#78953f;' contenteditable=''>"+str+"</span>"
}

function singleSelectionHighLight(str,spec){
    let type = ""
    if(spec[0] == "."){
        type = spec.substring(1,spec.length)
    }
    if(!(type == "var" || type == "func" || type == "arg")){
        type = ""
    }
    let name = str.substring(1,str.length-1)
    return "<a class='select-variable " + name + "-var' style='color:#c47635; cursor: pointer;' contenteditable='' type='"+type+"'>"+str+"</a>" + "<span style='color:#d2416e;' contenteditable=''>"+spec+"</span>"
}

function nonamePropositionHighLight(str){
    return "<span style='color:#2a6fa3;' contenteditable=''>"+str+"</span>"
}

function commentHighlight(str){
    return "<span style='color:#6e7781;' contenteditable=''>"+str+"</span>"
}

function handleSingleStatement(opb){
    let result = ""
    for(let op_id = 0; op_id < opb.length; op_id++){
        let op = opb[op_id]

        if(op[0] == "*"){
            result += commentHighlight(op)
        }else if(isDefaultString(op)){
            result += defaultStringHighlight(op)
        }else if(isOperatorString(op)){
            result += operatorHighLight(op)
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
            result += singleSelectionHighLight(value,spec)
        }else if(op[0] == "{"){
            result += nonamePropositionHighLight(op)
        }else{
            result += operandHighlight(op)
        }
    }
    return result
}

export function acceptedInputKey(ch){
    return typeof ch === "string" && ch.length == 1 &&
        ((ch <= "9" && ch >= "0") || (ch <= "z" && ch >= "a") || (ch <= "Z" && ch >= "A") ||
          ch == "~" || ch == ">" || ch == "=" || ch == "<" || ch == "(" || ch == ")" || ch == "{" ||
          ch == "}" || ch == "'" || ch == "\"" || ch == "!" || ch == "|" || ch == "&" || ch == ":" || 
          ch == " " || ch == ";" || ch == "_")
}

export function analyseLTLCode(code) {
    let result = ""
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
        result += handleSingleStatement(opb)
        if(line_id < lines.length - 1){
            result += "\n"
        }
    }
    return result
}