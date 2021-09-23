import { SmartContractsService } from "./smartcontract.service"
import { ContextService } from "./context.serivce"
import { LtlService } from "./ltlpro.serivce"

/* -------Vulnerabilities------ */
var listVulnerabilities = [
    { id: 1, name: "Integer Overfow/Underflow", description: "The [] Out of range is a property of vulnerability", },
    { id: 2, name: "Reentrancy", description: "Reentrancy is a property of vulnerability", },
    { id: 3, name: "Self-destruction", description: "Self-destruction is a property of vulnerability", },
    { id: 4, name: "Timestamp Dependence", description: "Timestamp Dependence is a property of vulnerability", },
    { id: 5, name: "Skip Empty String Literal", description: "Skip Empty String Literal is a property of vulnerability", },
    { id: 6, name: "Uninitialized Storage Variable", description: "Uninitialized Storage Variable is a property of vulnerability", },
    { id: 7, name: "Others", description: "Vulnerability 3 is a property of vulnerability", },
]

export function GetVulnerabilities() {
    return listVulnerabilities
}

/* -------Smart Contracts-------- */
var listCommonSmartContracts = [
    { id: 1, name: "Mathematics for Engineering", date_modified: 1607110465663, type: "common" },
    { id: 2, name: "Property 2: Fairness", date_modified: 1608110465663, type: "common" },
    { id: 3, name: "Course competencies", date_modified: 1609110465663, type: "common" },
    { id: 4, name: "Build Web Apps with Vue JS 3 & Firebase", date_modified: 1608130465663, type: "common" },
    { id: 5, name: "Advanced Techniques for Modeling and Verification", date_modified: 1608130765663, type: "common" },
    { id: 6, name: "Mathematics for Engineering 2nd", date_modified: 1607110465663, type: "common" },
    { id: 7, name: "Property 2: Fairness 2nd", date_modified: 1608110465663, type: "common" },
    { id: 8, name: "Course competencies 2nd", date_modified: 1609110465663, type: "common" },
    { id: 9, name: "Build Web Apps with Vue JS 3 & Firebase 2nd", date_modified: 1608130465663, type: "common" },
    { id: 10, name: "Advanced Techniques for Modeling and Verification 2nd", date_modified: 1608130765663, type: "common" },
]

var listPrivateSmartContracts = [
    { id: 11, name: "Blind Action", date_modified: 1609110465663, type: "private" },
    { id: 12, name: "Property 2: Fairness what's up", date_modified: 1608130765663, type: "private" },
    { id: 13, name: "Modules CPNC", date_modified: 1607110465663, type: "private" },
    { id: 14, name: "Blind Action 2nd", date_modified: 1609110465663, type: "private" },
    { id: 15, name: "Property 2: Fairness what's up 2nd", date_modified: 1608130765663, type: "private" },
    { id: 16, name: "Modules CPNC 2nd", date_modified: 1607110465663, type: "private" },
]

var listPendingSmartContracts = [
    { id: 17, name: "alabama ola", date_modified: 1607110465663, type: "pending" },
    { id: 18, name: "perry the platypus", date_modified: 1608130465663, type: "pending" },
]

export async function GetCommonSmartContracts() {
    //return listCommonSmartContracts
    return await (await SmartContractsService.GetCommonSmartContracts()).data;
}

export function GetPrivateSmartContracts() {
    return listPrivateSmartContracts
}

export function GetPendingSmartContracts() {
    return listPendingSmartContracts
}

export function GetSmartContractFunctionInfor(list_smart_contract) {
    const data_example = {
        1: {
            name: "Mathematics for Engineering",
            list_gvs: [{ name: "GV1" }, { name: "GV2" }],
            list_functions: [{ name: "Function 1", list_lvs: [{ name: "LV1" }, { name: "LV2" }, { name: "LV3" }, { name: "LV4" }], },
                { name: "Function 2", list_lvs: [{ name: "AK1" }, { name: "AK2" }, { name: "AK3" }] },
                { name: "Function 3", list_lvs: [{ name: "MV1" }, { name: "MV2" }] },
                { name: "Function 4", list_lvs: [{ name: "TH1" }, { name: "TH2" }, { name: "TH3" }, { name: "TH4" }, { name: "TH5" }] }
            ]
        },
        2: {
            name: "Property 2: Fairness",
            list_gvs: [{ name: "GV1" }, { name: "GV2" }, { name: "GV3" }],
            list_functions: [{ name: "Function 1", list_lvs: [{ name: "LV1" }, { name: "LV2" }, { name: "LV3" }, { name: "LV4" }], },
                { name: "Function 2", list_lvs: [{ name: "AK1" }, { name: "AK2" }, { name: "AK3" }] },
                { name: "Function 3", list_lvs: [{ name: "MV1" }, { name: "MV2" }] },
                { name: "Function 4", list_lvs: [{ name: "TH1" }, { name: "TH2" }, { name: "TH3" }, { name: "TH4" }, { name: "TH5" }] }
            ]
        },
        3: {
            name: "Course competencies",
            list_gvs: [{ name: "GV1" }, { name: "GV2" }, { name: "GV6" }],
            list_functions: [{ name: "Function 1", list_lvs: [{ name: "LV1" }, { name: "LV2" }, { name: "LV3" }, { name: "LV4" }], },
                { name: "Function 2", list_lvs: [{ name: "AK1" }, { name: "AK2" }, { name: "AK3" }] },
                { name: "Function 3", list_lvs: [{ name: "MV1" }, { name: "MV2" }] },
                { name: "Function 4", list_lvs: [{ name: "TH1" }, { name: "TH2" }, { name: "TH3" }, { name: "TH4" }, { name: "TH5" }] }
            ]
        },
        4: {
            name: "Build Web Apps with Vue JS 3 & Firebase",
            list_gvs: [{ name: "GV1" }, { name: "GV2" }, { name: "GV5" }],
            list_functions: [{ name: "Function 1", list_lvs: [{ name: "LV1" }, { name: "LV2" }, { name: "LV3" }, { name: "LV4" }], },
                { name: "Function 2", list_lvs: [{ name: "AK1" }, { name: "AK2" }, { name: "AK3" }] },
                { name: "Function 3", list_lvs: [{ name: "MV1" }, { name: "MV2" }] },
                { name: "Function 4", list_lvs: [{ name: "TH1" }, { name: "TH2" }, { name: "TH3" }, { name: "TH4" }, { name: "TH5" }] }
            ]
        },
        5: {
            name: "Advanced Techniques for Modeling and Verification",
            list_gvs: [{ name: "GV1" }, { name: "GV2" }, { name: "GV8" }],
            list_functions: [{ name: "Function 1", list_lvs: [{ name: "LV1" }, { name: "LV2" }, { name: "LV3" }, { name: "LV4" }], },
                { name: "Function 2", list_lvs: [{ name: "AK1" }, { name: "AK2" }, { name: "AK3" }] },
                { name: "Function 3", list_lvs: [{ name: "MV1" }, { name: "MV2" }] },
                { name: "Function 4", list_lvs: [{ name: "TH1" }, { name: "TH2" }, { name: "TH3" }, { name: "TH4" }, { name: "TH5" }] }
            ]
        }
    }
    var response = {}
    for (let i = 0; i < list_smart_contract.length; i++) {
        if (list_smart_contract[i].id in data_example) {
            response[list_smart_contract[i].id] = data_example[list_smart_contract[i].id]
        }
    }
    return response
}

var SmartContractCode = {
    1: "1st smart contract code",
    2: "2nd smart contract code",
    3: "3rd smart contract code",
    4: "4th smart contract code",
    5: "5th smart contract code",
    6: "6th smart contract code",
    7: "7th smart contract code",
    8: "8th smart contract code",
    9: "9th smart contract code",
    10: "10th smart contract code",
    11: "11th smart contract code",
    12: "12th smart contract code",
    13: "13th smart contract code",
    14: "14th smart contract code",
    15: "15th smart contract code",
    16: "16th smart contract code",
    17: "17th smart contract code",
    18: "18th smart contract code"
}

export function GetSmartContractCode(id) {

    if (id in SmartContractCode) {
        return SmartContractCode[id]
    } else {
        return ""
    }
}

export function AddNewSmartContractsInfor(sc_id, sc_name, options) {
    if (options == "private") {
        listPrivateSmartContracts.push({ id: sc_id, name: sc_name, type: "private" })
    }
    if (options == "common") {
        listCommonSmartContracts.push({ id: sc_id, name: sc_name, type: "common" })
    }
    if (options == "pending") {
        listPendingSmartContracts.push({ id: sc_id, name: sc_name, type: "pending" })
    }
}
export async function AddNewSmartContracts(sc_id, sc_name, options) {
    // AddNewSmartContractsInfor(sc_id,sc_name,options)
    // SmartContractCode[sc_id] = code
    var d = new Date,
        dformat = [d.getFullYear(),
            d.getMonth() + 1, d.getDate()
        ].join('-') + ' ' + [d.getHours(),
            d.getMinutes(),
            d.getSeconds()
        ].join(':');
    await SmartContractsService.CreateSmartContracts(sc_id.words[0], sc_name, dformat, options)
}

export async function UpdateSmartContractCode(sc_id, name_sc, code) {
    // if(sc_id in SmartContractCode){
    //   SmartContractCode[sc_id] = code
    // }
    console.log(code)
    await SmartContractsService.UpdateSmartContracts(sc_id, name_sc)
}

function deleteSmartContractFromList(list, sc_id) {
    for (let i = 0; i < list.length; i++) {
        if (sc_id == list[i].id) {
            list.splice(i, 1)
            break
        }
    }
}
export function DeleteSmartContracts(sc_id, options) {
    if (options == "private") {
        deleteSmartContractFromList(listPrivateSmartContracts, sc_id)
    }
    if (options == "common") {
        deleteSmartContractFromList(listCommonSmartContracts, sc_id)
    }
    if (options == "pending") {
        deleteSmartContractFromList(listPendingSmartContracts, sc_id)
    }
}
/* ------Context------- */
export async function GetContext() {
    const response = await ContextService.GetAllContext()
    return response.data
}

export async function GetContextById(id_context) {
    const response = await ContextService.GetContextById(id_context)
    return response.data
}


/*---------CreateAndModiftyContext--------- */
export async function CreateContext(name, description, fomular) {
    return await ContextService.CreateContext(name, fomular, description)
}

/*---------DeleteContext-------- */
export async function DeleteContext(id_context) {
    return await ContextService.DeleteContext(id_context)
}

/*---------Update Context-------- */
export async function UpdateContext(id_context, ct_name, ct_description) {
    return await ContextService.UpdateContext(id_context, ct_name, ct_description)
}


/* ------LTL------- */

export async function GetLtl() {
    const response = await LtlService.GetAllLtl()
    return response.data
}

export async function GetLtlById(id_Ltl) {
    const response = await LtlService.GetLtlById(id_Ltl)
    return response.data
}

/*---------CreateAndModiftyLtl--------- */
export async function CreateLtl(name, description, fomular) {
    return await LtlService.CreateLtl(name, description, fomular);
}

/*---------DeleteLtl-------- */
export async function DeleteLtl(id_Ltl) {
    return await LtlService.DeleteLtl(id_Ltl)
}

/*---------Update Ltl-------- */
export async function UpdateLtl(id_Ltl, ct_name, ct_description, fomular) {
    return await LtlService.UpdateLtl(id_Ltl, ct_name, ct_description, fomular)
}