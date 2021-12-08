import { BaseService, ErrorWrapper, ResponseWrapper } from './base.js'

export class LTLTemplate extends BaseService {
  static get entity() {
    return 'ltlproperty'
  }

  static async getLTLTemplate() {
    try {
      const response = await this.request({ auth: true }).get(`${this.entity}/get-ltltemplate`)
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }
  static async createLTLTemplate(id, l_name, formular, l_formula, l_template_type, l_description,) {
    const param = {
      lteid: id,
      name: l_name,
      formula: formular,
      formula_text: l_formula,
      template_type: l_template_type,
      description: l_description,
      created_timestamp: Date.now()
    }
    console.log(param)
    try {
      const response = await this.request({ auth: true }).post(`${this.entity}/get-ltltemplate`, param)
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }
  static async updateLTLTemplate(id, l_name, l_formula, l_template_type, l_description,fomular_code) {
    const param = {
      lteid: id,
      name: l_name,
      formula: l_formula,
      formula_text: fomular_code,
      template_type: l_template_type,
      description: l_description,
      created_timestamp: Date.now()
    }
    try {
      const response = await this.request({ auth: true }).put(`${this.entity}/get-ltltemplate`, param)
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }
  static async deleteLTLTemplate(id) {
    try {
      const response = await this.request({ auth: true }).delete(`${this.entity}/get-ltltemplate?lteid=${id}`)
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }
}
