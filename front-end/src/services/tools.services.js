import { BaseService, ErrorWrapper, ResponseWrapper } from './base.js'

export class ToolsServices extends BaseService{
    static get entity () {
        return 'tools'
    }
    
    static async generateCpnModel (selectedSc,selectedContext,selectedVulnerability,initialMarkingInfor) {
        try {
          const response = await this.request({ auth: true }).post(`${this.entity}/generate-cpn-model`,{"selected-smartcontract":selectedSc,
        "selected-context":selectedContext,"selected-vulnerability":selectedVulnerability,"initial-marking":initialMarkingInfor})
          return new ResponseWrapper(response, response.data)
        } catch (error) {
          throw new ErrorWrapper(error)
        }
    }
    
    static async checkingCpnModel (generateData) {
        try {
          const response = await this.request({ auth: true }).post(`${this.entity}/check-cpn-model`,{"hcpn-data":generateData})
          return new ResponseWrapper(response, response.data)
        } catch (error) {
          throw new ErrorWrapper(error)
        }
    }

    static async SaveCheckedBatchSmartContract (selectedSc,selectedContext,selectedVulnerability,initialMarkingInfor,hcpnData,checkingResult) {
      try {
        const response = await this.request({ auth: true }).post(`${this.entity}/save-checking-batch`,{"selected-smartcontract":selectedSc,
        "selected-context":selectedContext,"selected-vulnerability":selectedVulnerability,"initial-marking":initialMarkingInfor,
        "hcpn-data":hcpnData,"checking-result":checkingResult})
        return new ResponseWrapper(response, response.data)
      } catch (error) {
        throw new ErrorWrapper(error)
      }
  }
}
