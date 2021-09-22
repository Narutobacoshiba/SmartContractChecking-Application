import { BaseService, ErrorWrapper, ResponseWrapper } from "./base";
export class LtlService extends BaseService{
    /* Type Object API */
    static getUnity() {
        return 'ltl'
    }
    /*---------Get All Of Row In  Table---------- */
    static async GetAllLtl() {
        try {
            const response = await this.request({ auth: true }).get(`${this.getUnity()}/api/`)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }

    /*---------Create New--------- */
    static async CreateLtl(ltl_name,formula,description) {
        try {
            const paraData = {
                "name": ltl_name,
                "formula": formula,
                "description": description
                //edit here
            }
            const response = await this.request({ auth: true }).post(`${this.getUnity()}/api/`, paraData)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }


    /*---------Update Smartcontract--------- */
        static async UpdateLtl(name,formula,ct_description) {
        const ContextById = await this.request({ auth: true }).get(`${this.getUnity()}/ltlbyid?id=${id}`)
        // console.log(ContextById,ct_name,ct_description)
        try {
            const paraData = {
                "name": ltl_name,
                "formula": formula,
                "description": ct_description
            }
            }
            const response = await this.request({ auth: true }).put(`${this.getUnity()}/api/`, paraData)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            console.log(error)
            throw new ErrorWrapper(error, message)
           
        }

    /*---------Delete Smartcontract--------- */
    static async DeleteLtl(id) {
        try {
            console.log(id)
            const response = await this.request({ auth: true }).delete(`${this.getUnity()}/api/?id=${id}`)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }

    /*---------Get Context By ID--------- */
    static async GetLtlById(id) {
        try {
            const response = await this.request({ auth: true }).get(`${this.getUnity()}/ltlbyid?id=${id}`)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
}