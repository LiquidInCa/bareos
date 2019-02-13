import Vue from 'vue'
import Router from 'vue-router'
import Home from './views/Home.vue'
import BackupHistory from './views/BackupHistory.vue'

Vue.use(Router)

export default new Router({
  mode: 'history',
  base: process.env.BASE_URL,
  routes: [
    {
      path: '/',
      name: 'home',
      component: Home
    },
    {
      path: '/backup/history',
      name: 'BackupHistory',
      component: BackupHistory
    },
    {
      path: '/jobs',
      name: 'jobs',
      component: () => import('./views/Jobs.vue')
    },
    {
      path: '/bconsole',
      name: 'bconsole',
      // route level code-splitting
      // this generates a separate chunk (about.[hash].js) for this route
      // which is lazy-loaded when the route is visited.
      component: () => import(/* webpackChunkName: "about" */ './views/BConsole.vue')
    },
    {
      path: '/console',
      name: 'console',
      // route level code-splitting
      // this generates a separate chunk (about.[hash].js) for this route
      // which is lazy-loaded when the route is visited.
      component: () => import(/* webpackChunkName: "about" */ './views/Console.vue')
    },
    {
      path: '/bconsole/:id',
      name: 'dedicated-bconsole',
      // route level code-splitting
      // this generates a separate chunk (about.[hash].js) for this route
      // which is lazy-loaded when the route is visited.
      component: () => import(/* webpackChunkName: "about" */ './views/BConsole.vue')
    },
    {
      path: '/about',
      name: 'about',
      // route level code-splitting
      // this generates a separate chunk (about.[hash].js) for this route
      // which is lazy-loaded when the route is visited.
      component: () => import(/* webpackChunkName: "about" */ './views/About.vue')
    }
  ]
})