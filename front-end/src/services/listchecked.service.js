
import { BaseService, ErrorWrapper, ResponseWrapper } from "./base";
export class CheckedService extends BaseService{
    static getUnity() {
        return '/select-sc'
    }

    static async GetCommonSmartContracts() {
        try {
            const response = await this.request({ auth: true }).get(`${this.getUnity()}/listofcheckedtransactions/`)
            console.log(response)
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
}