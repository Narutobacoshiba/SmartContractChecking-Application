import { BaseService, ErrorWrapper, ResponseWrapper } from "./base";
export class LTLService extends BaseService {
    /* Type Object API */
    static getUnity() {
        return 'ltl'
    }

    static async GetAllLTL() {
        try {
            const response = await this.request({ auth: true }).get(`${this.getUnity()}/api/`)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
    static async CreateLTL(ct_name, content, description) {
        try {
            const paraData = {
                "name": ct_name,
                "content": content,
                "description": description
            }
            const response = await this.request({ auth: true }).post(`${this.getUnity()}/api/`, paraData)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
    static async DeleteLTL(id) {
        try {
            console.log(id)
            const response = await this.request({ auth: true }).delete(`${this.getUnity()}/api/?id=${id}`)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
    static async UpdateLTL(id, ct_name, ct_description) {
        const ContextById = await this.request({ auth: true }).get(`${this.getUnity()}/ltlbyid?id=${id}`)
        try {
            const paraData = {
                "id": id,
                "name": ct_name,
                "content": ContextById.data.content,
                "description": ct_description
            }
            const response = await this.request({ auth: true }).put(`${this.getUnity()}/api/`, paraData)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            console.log(error)
            throw new ErrorWrapper(error, message)

        }
    }
    static async GetLTLById(id) {
        try {
            const response = await this.request({ auth: true }).get(`${this.getUnity()}/ltlbyid?id=${id}`)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
}