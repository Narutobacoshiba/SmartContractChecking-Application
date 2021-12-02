import { Http } from './http.js'

export class BaseService {
  static get entity () {
    throw new Error('entity getter not defined')
  }

  static request (status = { auth: false }) {
    return new Http(status)
  }

  static responseWrapper (...rest) {
    return new ResponseWrapper(...rest)
  }

  static errorWrapper (...rest) {
    return new ErrorWrapper(...rest)
  }
}


function _getStatusMessage (status) {
  let message = ''
  switch (status) {
    case 200:
      message = 'All done. Request successfully executed'
      break
    case 201:
      message = 'Data successfully created'
      break
    case 400:
      message = 'Bad Request'
      break
    case 401:
      message = 'Need auth'
      break
    case 403:
      message = "Forbiden"
      break
    case 404:
      message = 'Not found'
      break
    case 503:
      message = 'Service unavailable. Try again later'
      break
    default:
      message = 'Something wrong. Client default error message'
      break
  }
  return message
}

function _getResponseErrorMessage (error) {
  if (error.response && error.response.data) return error.response.data
  if (error.response && error.response.statusText) return error.response.statusText
  return error.message === 'Network Error' ? 'Oops! Network Error. Try again later' : error.message
}


export class ResponseWrapper {
  constructor (response, data = {}, message) {
    this.data = data
    this.status = response.status
    this.statusMessage = _getStatusMessage(this.status)
    this.message = message || null
  }
}

export class ErrorWrapper extends Error {
  constructor (error) {
    super()
    this.status = error.response ? error.response.status : false
    this.statusMessage = _getStatusMessage(this.status)
    this.detail = error.response.data.detail || _getResponseErrorMessage(error)
  }
}