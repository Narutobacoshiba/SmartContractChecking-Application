import { BaseService, ErrorWrapper, ResponseWrapper } from "./base";
export default class CheckService extends BaseService {
    static getUnity() {
        return '/smartconstract'
    }

    static async callToolsCheckContext(id, nameCt, contentCt, descriptionCt, ctidCt) {
        const paraData = {
            cid: id,
            name: nameCt,
            content: contentCt,
            description: descriptionCt,
            ctid: ctidCt
        }
        console.log(paraData)
        try {
            const response = await this.request({ auth: true }).post('', paraData)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }

    static async callDCNTools(tName, tXml) {
        const paraData = {
            toolname: tName,
            xml: tXml
        };
        console.log(paraData)
        try {
            const response = await this.request({ auth: true }).post('/tools/', paraData)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }

    static async callUnfoldingTools(tName, tLna, tContext, tParam) {
        const paraData = {
            toolname: tName,
            lna: tLna,
            context: tContext,
            param: tParam
        };
        // console.log(paraData)
        try {
            const response = await this.request({ auth: true }).post('/tools/', paraData)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }

    static async callToolLTL(tName) {
        const paraData = {
            toolname: tName
            
        };
        console.log(paraData)
        try {
            const response = await this.request({ auth: true }).post('/tools/', paraData)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }

    static async callHelenaTools(tName) {
        const paraData = {
            toolname: tName
        };
        console.log(paraData)
        try {
            const response = await this.request({ auth: true }).post('/tools/', paraData)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
}