import $store from '../store'
import { AuthService } from '@/services/auth.js'
import cookie from 'vue-cookies'

export async function initCurrentUserStateMiddleware (to, from, next) {
  const currentUserId = $store.state.user.currentUser.id
  
  if (AuthService.hasRefreshToken() && !currentUserId) {
    try {
      await AuthService.debounceRefreshTokens()
      await $store.dispatch('user/getCurrent')
      next()
    } catch (e) {
      console.log(e)
    }
  } else {
    next()
  }  
}

export function checkAccessMiddleware (to, from, next) {
  const currentUserId = $store.state.user.currentUser.id
  const isAuthRoute = to.matched.some(record => record.meta.requiresAuth)

  if (isAuthRoute){
        if (currentUserId) {
          if((!$store.state.data.used) && cookie.isKey("_dt"+currentUserId))
          {
            var data = cookie.get("_dt"+currentUserId)
            if($store.state.data.version == data.version)
            {
              $store.commit('data/SetAllData',data)
              $store.commit('data/SetUsedState',true)
            }
          }
          return next();
        }
        return next("/login");
  }

  const isGuestRoute = to.matched.some(record => record.meta.guest)
  if(isGuestRoute)
  {
    if (currentUserId) {
        return next("/home");
      }
      return next()
  }
  return next()
}

export function setPageTitleMiddleware (to, from, next) {
  const pageTitle = to.matched.find(record => record.meta.title)

  if (pageTitle) window.document.title = pageTitle.meta.title
  next()
}