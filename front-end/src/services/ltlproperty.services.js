import { BaseService, ErrorWrapper, ResponseWrapper } from './base.js'

export class LTLTemplate extends BaseService{
    static get entity () {
        return 'ltlproperty'
    }

    static async getLTLTemplate () {
        try {
          const response = await this.request({ auth: true }).get(`${this.entity}/get-ltltemplate`)
          return new ResponseWrapper(response, response.data)
        } catch (error) {
          throw new ErrorWrapper(error)
        }
      }
}
