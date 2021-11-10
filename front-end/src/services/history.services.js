import { BaseService, ErrorWrapper, ResponseWrapper } from './base.js'

export class HistoryServices extends BaseService{
    static get entity () {
        return 'history'
    }

    static async SaveCheckedBatchSmartContract (selectedSc,selectedContext,selectedVulnerability,initialMarkingInfor,hcpnData,checkedBatch) {
      try {
        const response = await this.request({ auth: true }).post(`${this.entity}/save-checked-batch`,{"selected-smartcontract":selectedSc,
        "selected-context":selectedContext,"selected-vulnerability":selectedVulnerability,"initial-marking":initialMarkingInfor,
        "hcpn-data":hcpnData,"checked-batch":checkedBatch})
        
        return new ResponseWrapper(response, response.data)
      } catch (error) {
        throw new ErrorWrapper(error)
      }
    }

    static async GetCheckedBatchSmartContract () {
      try {
        const response = await this.request({ auth: true }).get(`${this.entity}/get-checked-batch`)
        
        return new ResponseWrapper(response, response.data)
      } catch (error) {
        throw new ErrorWrapper(error)
      }
    }

    static async GetCheckedBatchByID (id) {
      try {
        const response = await this.request({ auth: true }).post(`${this.entity}/get-checked-batch`,{"cbsid":id})
        
        return new ResponseWrapper(response, response.data)
      } catch (error) {
        throw new ErrorWrapper(error)
      }
    }
}
