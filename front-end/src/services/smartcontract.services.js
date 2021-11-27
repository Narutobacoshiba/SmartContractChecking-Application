import { BaseService, ErrorWrapper, ResponseWrapper } from './base.js'

export class SmartContractService extends BaseService {
  static get entity() {
    return 'smartcontract'
  }

  static async getAllSmartContract() {
    try {
      const response = await this.request({ auth: true }).get(`${this.entity}/get_all`)
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }
  static async createAllSmartContract(s_id, s_name, s_type, s_content, s_description) {
    const param = {
      sid: s_id,
      name: s_name,
      type: s_type,
      content: s_content,
      description: s_description,
      created_timestamp: "1608110465663",
      aid: "0863e75515b4efeba7216d384091be00d18f149a7fa822807901fae602d723d0"
    }
    console.log(param)
    try {
      const response = await this.request({ auth: true }).post(`${this.entity}/crud-sc`, param)
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }

  static async getSmartContractInformation(list_ids) {
    try {
      const response = await this.request({ auth: true }).post(`${this.entity}/get_vfinfor`, { "ids": list_ids })
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }
  static async editSmartContract(sc_id, sc_name, sc_content, sc_type, sc_description) {
    const param = {
      sid: sc_id,
      name: sc_name,
      type: sc_type,
      created_timestamp: 1608110465663,
      description: sc_description,
      content: sc_content
    }
    console.log(param)
    try {
      const response = await this.request({ auth: true }).put(`${this.entity}/crud-sc`, param)
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }
  static async deleteSmartContract(sc_id) {
    try {
      const response = await this.request({ auth: true }).delete(`${this.entity}/crud-sc?sid=${sc_id}`)
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }
}
