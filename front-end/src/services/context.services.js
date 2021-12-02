import { BaseService, ErrorWrapper, ResponseWrapper } from './base.js'

export class ContextService extends BaseService {
  static get entity() {
    return 'context'
  }

  static async getAllContext() {
    try {
      const response = await this.request({ auth: true }).get(`${this.entity}/cpn-context-crud`)
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }
  static async editContext(_id, _name, _content, _context_type, _description) {
    const param = {
      ccid: _id,
      name: _name,
      content: _content,
      context_type: _context_type,
      description: _description
    }
    try {
      const response = await this.request({ auth: true }).put(`${this.entity}/cpn-context-crud`, param)
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }
  static async deleteContext(_id) {
    try {
      const response = await this.request({ auth: true }).delete(`${this.entity}/cpn-context-crud?ccid=${_id}`)
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }
  static async createContext(_id, _name, _type, _content, _description) {
    const param = {
      ccid: _id,
      name: _name,
      context_type: _type,
      content: _content,
      description: _description,
      created_timestamp: Date.now(),
      aid: "0863e75515b4efeba7216d384091be00d18f149a7fa822807901fae602d723d0"
    }
    try {
      const response = await this.request({ auth: true }).post(`${this.entity}/cpn-context-crud`, param)
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }

}
