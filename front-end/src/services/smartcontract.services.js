import { BaseService, ErrorWrapper, ResponseWrapper } from './base.js'

export class SmartContractService extends BaseService{
    static get entity () {
        return 'smartcontract'
    }

    static async getAllSmartContract () {
        try {
          const response = await this.request({ auth: true }).get(`${this.entity}/get_all`)
          return new ResponseWrapper(response, response.data)
        } catch (error) {
          throw new ErrorWrapper(error)
        }
      }

    static async getSmartContractInformation(list_ids){
      try {
        const response = await this.request({ auth: true }).post(`${this.entity}/get_vfinfor`,{"ids":list_ids})
        return new ResponseWrapper(response, response.data)
      } catch (error) {
        throw new ErrorWrapper(error)
      }
    }
}
