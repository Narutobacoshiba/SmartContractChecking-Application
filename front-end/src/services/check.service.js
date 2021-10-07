import { BaseService, ErrorWrapper, ResponseWrapper } from "./base";
export default class CheckService extends BaseService {
    static getUnity() {
        return '/smartconstract'
    }

    static async callToolsCheckContext(id,nameCt,contentCt,descriptionCt,ctidCt) {
        const paraData = {
            cid:id,
            name:nameCt,
            content:contentCt,
            description:descriptionCt,
            ctid:ctidCt
        }
        console.log(paraData)
        try {
            const response = await this.request({auth:true}).post('',paraData)
            return new ResponseWrapper(response,response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
}