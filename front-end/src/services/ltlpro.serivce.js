import { BaseService, ErrorWrapper, ResponseWrapper } from "./base";
export class LtlService extends BaseService {
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
    static async CreateLtl(ltl_name, description, fomular) {
        try {
            const paraData = {
                "name": ltl_name,
                "fomular": fomular,
                "description": description,
                "type": "Property",
                "tpid": "2"
            }
            const response = await this.request({ auth: true }).post(`${this.getUnity()}/api/`, paraData)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }


    /*---------Update Smartcontract--------- */
    static async UpdateLtl(id, ltl_name, description, fomular) {
        // const LTLById = await this.request({ auth: true }).get(`${this.getUnity()}/ltlbyid?id=${id}`)
        // console.log(ContextById,ct_name,ct_description)
        try {
            const paraData = {
                "id": id,
                "name": ltl_name,
                "fomular": fomular,
                "description": description,
                "type": "Property",
                "tpid": "1",
            }

            const response = await this.request({ auth: true }).put(`${this.getUnity()}/api/`, paraData)
            return new ResponseWrapper(response, response.data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            console.log(error)
            throw new ErrorWrapper(error, message)

        }
    }

    /*---------Delete Smartcontract--------- */
    static async DeleteLtl(id) {
        try {
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