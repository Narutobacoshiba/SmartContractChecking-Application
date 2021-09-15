const NATokens = {
    '&': 'and',
    '!': 'not',
    '^': 'or',
}

const ATokens = {
    'F': 'finnaly',
    'G': 'global',
    'U': 'until',
}

function isAlpha(ch){
    return typeof ch === "string" && ch.length === 1
           && (ch >= "a" && ch <= "z" || ch >= "A" && ch <= "Z");
}

function isValidNaming(params) {
    for(let i=0; i<params.length; i++){
        if(!isAlpha(params[i]) && params[i] != '_'){
            return false
        }
    }   
    return true
}

function notSpecChar(ch) {
    return !(ch in NATokens) && !(ch in ATokens)
}


export function DetectLTLFormatError(ltl_code){
    var error = {detail: "", addr: []}

    var listTokens = []
    var left_level_err = []
    var right_level_err = []
    var naming_err = []
    var level = 0
    var temp = ""
    var st_id = 0

    for(let i=0; i<ltl_code.length; i++){
        if(ltl_code[i] == '('){
            level+=1
            if(level <= 0){
                level = 1
            }else{
                left_level_err.push([i,i+1])
            }

            if(temp.length > 0){
                if(isValidNaming(temp)){
                    listTokens.push([temp,st_id,i])
                    temp = ""
                    st_id = i+1
                }else{
                    naming_err.push([temp,st_id,i])
                }
            }
            listTokens.push([ltl_code[i],i,i+1])
        }else if(ltl_code[i] == ')'){
            level -= 1
            if(level < 0){
                right_level_err.push([i,i+1])
            }else{
                if(left_level_err.length > 0){
                    left_level_err.pop()
                }
            }
            if(temp.length > 0){
                if(isValidNaming(temp)){
                    listTokens.push([temp,st_id,i])
                    temp = ""
                    st_id = i+1
                }else{
                    naming_err.push([temp,st_id,i])
                }
            }
            listTokens.push([ltl_code[i],i,i+1])
        }else if(ltl_code[i] in NATokens){
            listTokens.push([ltl_code[i],i,i+1])
            if(temp.length > 0){
                if(isValidNaming(temp)){
                    listTokens.push([temp,st_id,i])
                    temp = ""
                    st_id = i+1
                }else{
                    naming_err.push([temp,st_id,i])
                }
            }
        }else if(ltl_code[i] in ATokens && (ltl_code[i+1] == ' ' || ltl_code[i+1] == '(')){
            listTokens.push([ltl_code[i],i,i+1])
        }else if(ltl_code[i] == ' ' || i == ltl_code.length - 1){
            if(temp.length > 0){
                if(isValidNaming(temp)){
                    listTokens.push([temp,st_id,i])
                    temp = ""
                    st_id = i+1
                }else{
                    naming_err.push([temp,st_id,i])
                }
            }
        }else{
            temp = temp + ltl_code[i]
        }
    }

    if(left_level_err.length > 0){
        error.detail = "too many '('"
        error.addr = left_level_err
        return error
    }
    if(right_level_err.length > 0){
        error.detail = "too many ')'"
        error.addr = right_level_err
        return error
    }
    if(naming_err.length > 0){
        error.detail = "invalid naming"
        error.addr = naming_err
        return error
    }
    
    var list_var = {0:[]}
    var listinlvele = []
    var inlevel = 0
    for(let i=0; i<listTokens.length; i++){
        if(listTokens[i][0] == '('){
            inlevel+=1    
            listinlvele.push(listTokens[i])
            if(!(inlevel in list_var)){
                list_var[inlevel] = []
            }
        }else if(listTokens[i][0] == ')'){
            inlevel-=1
            var lastinlevel = listinlvele.pop()
            list_var[inlevel].push(["param",lastinlevel[1],listTokens[i][2]])
        }else{
            if(!(inlevel in list_var)){
                list_var[inlevel] = []
            }
            list_var[inlevel].push(listTokens[i])
        }
    }
    
    for (const key in list_var) {
        var value = list_var[key]
        for(let i=0; i<value.length; i++){
            let v = value[i][0]
            if(notSpecChar(v)){
                if(i < (value.length-1) && (notSpecChar(value[i+1][0]) || value[i+1][0] == '!' || value[i+1][0] == 'F' || value[i+1][0] == 'G')){
                    error.detail = "proposition be followed by invalid operator ('"+value[i+1][0]+"')"
                    error.addr = [[value[i][1],value[i][2]]]
                    return error
                }
            }else {
                if(v == '!' || v == 'F' || v == 'G'){
                    if(i == (value.length - 1)){
                        error.detail = "'+"+v+"' operator cannot be followed by 'empty'"
                        error.addr = [[value[i][1],value[i][2]]]
                        return error
                    }else if(value[i+1][0] == 'U' || value[i+1][0] == '^' || value[i+1][0] == '&'){
                        error.detail = "'+"+v+"' operator cannot be followed by '"+value[i+1][0]+"'"
                        error.addr = [[value[i][1],value[i][2]]]
                        return error
                    }
                }else if(v == 'U' || v == '^' || v == '&'){
                    if(i == (value.length - 1)){
                        error.detail = "'+"+v+"' operator cannot be followed by 'empty'"
                        error.addr = [[value[i][1],value[i][2]]]
                        return error
                    }else if(i == 0){
                        error.detail = "'+"+v+"' operator cannot stand behind  'empty'"
                        error.addr = [[value[i][1],value[i][2]]]
                        return error
                    }else if(value[i-1][0] == 'F' || value[i-1][0] == '!' || value[i-1][0] == 'G'){
                        error.detail = "'+"+v+"' operator cannot stand behind '"+value[i+1][0]+"'"
                        error.addr = [[value[i][1],value[i][2]]]
                        return error
                    }
                }
            }
        }
    }

    return error
}

export function extractTokensTag(ltl_code) {
    var listTokens = []
    var temp = ""
    var st_id = 0

    for(let i=0; i<ltl_code.length; i++){
        if(ltl_code[i] == '('){
            listTokens.push(['opl',i,i+1])
            if(temp.length > 0){
                listTokens.push(['opr',st_id,i])
                temp = ""
                st_id = i+1 
            }           
        }else if(ltl_code[i] == ')'){
            listTokens.push(['opl',i,i+1])
            if(temp.length > 0){
                listTokens.push(['opr',st_id,i])
                temp = ""
                st_id = i+1 
            } 
        }else if(ltl_code[i] in NATokens){
            listTokens.push(['opt',i,i+1])
            if(temp.length > 0){
                listTokens.push(['opr',st_id,i])
                temp = ""
                st_id = i+1 
            }
        }else if(ltl_code[i] in ATokens && (ltl_code[i+1] == ' ' || ltl_code[i+1] == '(')){
            listTokens.push(['opt',i,i+1])
        }else if(ltl_code[i] == ' ' || i == ltl_code.length - 1){
            if(temp.length > 0){
                listTokens.push(['opr',st_id,i])
                temp = ""
                st_id = i+1 
            }
        }else{
            temp = temp + ltl_code[i]
        }
    }
    return listTokens
}