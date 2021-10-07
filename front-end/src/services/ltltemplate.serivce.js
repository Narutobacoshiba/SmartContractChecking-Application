import { BaseService, ErrorWrapper, ResponseWrapper } from "./base";
export class ltltemplateService extends BaseService {
    /* Type Object API */
    static getUnity() {
        return 'ltltemplate'
    }
    static async GetAllltltemplates() {
        try {
            const response = await this.request({ auth: true }).get(`${this.getUnity()}/api/`)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
    static async GetLtltemplteById(id) {
        try {
            const response = await this.request({ auth: true }).get(`${this.getUnity()}/ltltemplate?id=${id}`)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }

    }

}