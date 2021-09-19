import { BaseService, ErrorWrapper, ResponseWrapper } from "./base";
export class ContextService extends BaseService{
    /* Type Object API */
    static getUnity() {
        return 'context'
    }
    /*---------Get All Of Row In Context Table---------- */
    /*
     * Using baseSerivce(axios) to send request to BackEnd
     * return a type ResponseWrapper having data of Backend
    */
    static async GetAllContext() {
        try {
            const response = await this.request({ auth: true }).get(`${this.getUnity()}/api/`)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
    /* ------------- Create A Context In Database------------ */
    static async CreateContext(ct_name,content,description) {
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
    /*---------Delete Context--------- */
    static async DeleteContext(id) {
        try {
            console.log(id)
            const response = await this.request({ auth: true }).delete(`${this.getUnity()}/api/?id=${id}`)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
    /*---------Update Context--------- */
    static async UpdateContext(id, ct_name,ct_description) {
        const ContextById = await this.request({ auth: true }).get(`${this.getUnity()}/contextbyid?id=${id}`).data

        try {
            const paraData = {
                "id": id,
                "name": ct_name,
                "content": ContextById.content ,
                "type": ct_description
            }
            console.log(paraData)
            const response = await this.request({ auth: true }).put(`${this.getUnity()}/api/`, paraData)
            // const data = {
            //     content: response.data.data,
            //     headers: response.headers['']
            // }
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
    /*---------Get Context By ID--------- */
    static async GetContextById(id) {
        try {
            const response = await this.request({ auth: true }).get(`${this.getUnity()}/contextbyid?id=${id}`)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
}