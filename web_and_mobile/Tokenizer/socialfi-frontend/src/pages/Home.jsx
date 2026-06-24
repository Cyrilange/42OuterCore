import React from 'react'
import Menu from '../conponents/Menu'
import Footer from '../conponents/Footer'
import Action from '../conponents/Action'
import './home.css'

function Home() {
  return (
	<div>
		<div className='home'>
			<Menu />
			<Action />
			<Footer />
		</div>
	</div>
  )
}

export default Home