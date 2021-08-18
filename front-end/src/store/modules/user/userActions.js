import { UsersService } from '@/services/users.js'

export default {
  getCurrent ({ commit }) {
    return UsersService.getCurrent()
      .then(user => commit('SET_CURRENT_USER', user.data))
      .catch(error => {error})
  }
}
