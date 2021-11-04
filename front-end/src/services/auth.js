import axios from 'axios'

/* import { Http } from './http.js' */
import { ResponseWrapper, ErrorWrapper } from './base.js'
import $store from '../store'
import $router from '../router'

import { API_URL } from '../.env'

export class AuthService {
  /**
   ******************************
   * @API
   ******************************
   */
  
  static async makeLogin ({ username, password }) {
    try {
      const response = await axios.post(`${API_URL}/auth/login`,{username, password}, {useCredentails: true})
      _setAuthData({
        accessToken: response.data.accessToken,
        exp: _parseTokenData(response.data.accessToken).exp
      })
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }

  static async makeLogout () {
    try {
      /* const response = await new Http({ auth: true }).post('auth/logout', {}, { useCredentails: true }) */
      _resetAuthData()

      $router.push({ name: 'Login' }).catch(() => {})
      /* return new ResponseWrapper(response, response.data) */
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }

  static async makeRegister ({username, email, password }) {
    try {
      const response = await axios.post(`${API_URL}/auth/register`,
        {username, email, password}, { useCredentails: true })

      return new ResponseWrapper(response, response.data)
    } catch (error) {
      throw new ErrorWrapper(error)
    }
  }


  static async refreshTokens () {
    try {
      var username = $store.state.user.currentUser.username
      const response = await axios.post(`${API_URL}/auth/refresh-tokens`,{ username },{useCredentails: true})
      _setAuthData({
        accessToken: response.data.accessToken,
        exp: _parseTokenData(response.data.accessToken).exp
      })
      return new ResponseWrapper(response, response.data)
    } catch (error) {
      _resetAuthData()
      $router.push({ name: 'Login' }).catch(() => {})
      throw new ErrorWrapper(error)
    }
  }

  static debounceRefreshTokens = this._debounce(() => {
    return this.refreshTokens()
  }, 100)

  /**
   ******************************
   * @METHODS
   ******************************
   */

  static isAccessTokenExpired () {
    const accessTokenExpDate = $store.state.auth.accessTokenExpDate - 10
    const nowTime = Math.floor(new Date().getTime() / 1000)

    return accessTokenExpDate <= nowTime
  }

  static hasRefreshToken () {
    return Boolean(localStorage.getItem('refreshToken'))
  }

  static setRefreshToken (status) {
    if (!['', 'true'].includes(status)) {
      throw new Error(`setRefreshToken: invalid value ${status}; Expect one of ['', 'true']`)
    }

    localStorage.setItem('refreshToken', status)
  }

  static getBearer () {
    if("accessToken" in localStorage){
      return localStorage.getItem('accessToken')
    }else{
      return ""
    }
  }

  static setBearer (accessToken) {
    localStorage.setItem('accessToken', accessToken)
  }

  /*
   *tham khảo https://stackoverflow.com/questions/35228052/debounce-function-implemented-with-promises
   */
  static _debounce (inner, ms = 0) {
    let timer = null
    let resolves = []

    return function () {
      clearTimeout(timer)
      timer = setTimeout(() => {
        const result = inner()
        resolves.forEach(r => r(result))
        resolves = []
      }, ms)

      return new Promise(resolve => resolves.push(resolve))
    }
  }
}

/**
 ******************************
 * @private_methods
 ******************************
 */

function _parseTokenData (accessToken) {
  let payload = ''
  let tokenData = {}

  try {
    payload = accessToken.split('.')[1]
    tokenData = JSON.parse(atob(payload))
  } catch (error) {
    throw new Error(error)
  }

  return tokenData
}

function _resetAuthData () {
  // reset userData
  $store.commit('user/SET_CURRENT_USER', {})
  $store.commit('auth/SET_ATOKEN_EXP_DATE', null)

  // reset pageData
  $store.commit('data/resetAll')
  $store.commit('views/resetAll')
  // reset tokens
  AuthService.setRefreshToken('')
  AuthService.setBearer('')
}

function _setAuthData ({ accessToken, exp } = {}) {
  AuthService.setRefreshToken('true')
  AuthService.setBearer(accessToken)
  $store.commit('auth/SET_ATOKEN_EXP_DATE', exp)
}