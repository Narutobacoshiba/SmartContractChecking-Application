function isEscapeCharacter(ch){
    return typeof ch === "string" && ch.length === 1
           && (ch == " " || ch == "\b" || ch == "\f" || ch == "\n" || ch == "\r" || 
               ch == "\t" || ch == "\v" || ch == "\0" || ch == "{" || ch == "}" || ch == "'" || ch == "\"");
}

function isOperatorString(str){
    return typeof str === "string"
           && (str == "F" || str == "G" || str == "U" || str == "!" || str == "|" || str == "&" || str == "=>" ||
               str == ">" || str == "<" || str == ">=" || str == "<=" || str == "==" || str == "!=")
}

function isDefaultString(str) {
    return typeof str === "string"
           && (str == "const" || str == "proposition" || str == "property")
}

function defaultStringHighlight(str,err){
    if(err == "")
    return "<span style='color:#3376a8;' contenteditable=''>"+str+"</span>"
}

/* function isAcceptedName(str){
    for(let i = 0; i < str.length; i++){
        if(!((str[i] >= "a" && str[i] <= "z") || (str[i] >= "A" && str[i] <= "Z") || (str[i] >= "0" && str[i] <= "9") || str[i] == "_")){
            return false
        }
    }
    return true
} */
function operandHighlight(str,err){
    /* let value = ""
    if(isAcceptedName(str)){
        value = "<span style='color:#404447;' contenteditable=''>"+str+"</span>"
    }else{
        value = "<span style='color:#404447;text-decoration: underline;text-decoration-color: red;text-decoration-style:wavy;' contenteditable=''>"+str+"</span>"
    } */
    if(err == ""){
        return "<span style='color:#404447;' contenteditable=''>"+str+"</span>"
    }else{
        return "<span style='color:#404447;text-decoration: underline;text-decoration-color: red;text-decoration-style:wavy;' contenteditable=''>"+str+"</span>"
    }
}

function operatorHighLight(str,err){
    if(err == ""){
        return "<span style='color:#78953f;' contenteditable=''>"+str+"</span>"
    }else{
        return "<span style='color:#78953f;' contenteditable=''>"+str+"</span>"
    }
}

function singleSelectionHighLight(str,spec){
    let type = ""
    if(spec[0] == "."){
        type = spec.substring(1,spec.length)
    }
    if(!(type == "var" || type == "func" || type == "arg")){
        type = ""
    }
    return "<a style='color:#c47635; cursor: pointer;' contenteditable='' type='"+type+"'>"+str+"</a>" + "<span style='color:#d2416e;' contenteditable=''>"+spec+"</span>"
}

function nonamePropositionHighLight(str,err){
    let value = "<span style='color:#2a6fa3;' contenteditable=''>{</span>"

    if(str[str.length-1] == "}"){
        value += handleSingleStatement(str.substring(1,str.length-1))
        value += "<span style='color:#2a6fa3;' contenteditable=''>}</span>"
    }else{
        value += handleSingleStatement(str.substring(1,str.length))
    }
    if(err == "")
    return value
}

function infix2posfix(opb){
    console.log(opb)
    let error_handle = {}
    let opt_stack = []
    let opr_stack = []
    let count = 0

    while(count < opb.length){
        if(opb[count] == "("){
            opr_stack.push(count)
        }else if(opb[count] == ")"){
            let temp = opr_stack.pop()
            while(temp != undefined && opb[temp] != ")"){
                opt_stack.push(temp)
                temp = opr_stack.pop()
            }
            if(temp == undefined){
                error_handle[count] = "to manny ')' character"
                return error_handle
            }
        }
        count+=1
    }
    return {}
}

function handleSyntaxError(opb){
    console.log(opb[0])
    if(opb[0] == "proposition"){
        let start_def = 0;
        while(opb[start_def] != ":"){
            start_def += 1
        }
        let errors = infix2posfix(opb.slice(start_def+1));
        console.log(errors)
        let ret = {}
        for (const [key, value] of Object.entries(errors)) {
            ret[key + start_def + 1] = value
        }
        return ret
    }
    return {}
}

function handleSingleStatement(opb){
    let result = ""

    let errors = handleSyntaxError(opb)
    for(let op_id = 0; op_id < opb.length; op_id++){
        let op_error = ""
        if(op_id in errors){
            op_error = errors[op_id]
        }
        let op = opb[op_id]
        if(isDefaultString(op)){
            result += defaultStringHighlight(op,op_error)
        }else if(isOperatorString(op,op_error)){
            result += operatorHighLight(op,op_error)
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
            result += nonamePropositionHighLight(op,op_error)
        }else{
            result += operandHighlight(op,op_error)
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
    let lines = code.split(";")

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

                if(line[i] == "'" || line[i] == "\""){
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
            result += ";"
        }
    }
    return result
}