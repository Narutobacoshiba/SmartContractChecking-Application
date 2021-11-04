import { BaseService, ErrorWrapper, ResponseWrapper } from './base.js'

export class UsersService extends BaseService {
  static get entity () {
    return 'users'
  }

  static async getCurrent () {
    try {
      const response = await this.request({ auth: true }).get('/auth/current')
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      const message = error.response.data ? error.response.data.detail : error.response.statusText
      throw new ErrorWrapper(error, message)
    }
  }
}