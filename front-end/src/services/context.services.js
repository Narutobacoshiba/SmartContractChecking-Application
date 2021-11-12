import { BaseService, ErrorWrapper, ResponseWrapper } from './base.js'

export class ContextService extends BaseService{
    static get entity () {
        return 'context'
    }

    static async getAllContext () {
        try {
          const response = await this.request({ auth: true }).get(`${this.entity}/get-all`)
          return new ResponseWrapper(response, response.data)
        } catch (error) {
          throw new ErrorWrapper(error)
        }
      }
}
