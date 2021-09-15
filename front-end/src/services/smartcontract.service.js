import { BaseService, ErrorWrapper, ResponseWrapper } from "./base";
export class SmartContractsService extends BaseService {
    static SMARTCONTRACT_API_ENDPOINT = `${this.getUnity()}/api/`

    static getUnity() {
        return '/smartconstract'
    }
    /* Get All Common SmartContract */
    static async GetCommonSmartContracts() {
        try {
            const response = await this.request({ auth: true }).get("/smartconstract/api/")
            const data = {
                content: response.data.data,
                headers: response.headers['']
            }
            return new ResponseWrapper(response, data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }

    static async GetPrivateSmartContracts() {
        try {
            const response = await this.request({ auth: true }).get(`${this.entity}?type=private`)
            const data = {
                content: response.data.data,
                headers: response.headers['']
            }
            return new ResponseWrapper(response, data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
    static async GetPendingSmartContracts() {
        try {
            const response = await this.request({ auth: true }).get(`${this.entity}?type=pending`)
            const data = {
                content: response.data.data,
                headers: response.headers['']
            }
            return new ResponseWrapper(response, data)
        } catch (error) {
            const message = error.response.data ? error.response.data.error : error.response.statusText
            throw new ErrorWrapper(error, message)
        }
    }
}