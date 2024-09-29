import React, { useState } from 'react';
import { initializeApp } from 'firebase/app';
import { getDatabase, ref, set } from 'firebase/database';
import './App.css'; // Importing the CSS

// Firebase configuration
const firebaseConfig = {
  apiKey: "AIzaSyAnodZtia7P5b7HAaO_HC5gzuSnfbcPrs0",
  authDomain: "traffic-light-43560.firebaseapp.com",
  databaseURL: "https://traffic-light-43560-default-rtdb.firebaseio.com",
  projectId: "traffic-light-43560",
  storageBucket: "traffic-light-43560.appspot.com",
  messagingSenderId: "190465972257",
  appId: "1:190465972257:web:2f3dffee4ef7e545776b60",
  measurementId: "G-N121R3BXGW"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

const TrafficLightControl = () => {
  const [status, setStatus] = useState('Firebase initialized successfully');

  // Function to toggle LED color
  const toggleLED = (color) => {
    set(ref(database, 'ledControl'), { color })
      .then(() => setStatus(`${color} LED toggled`))
      .catch((error) => setStatus(`Error: ${error.message}`));
  };

  return (
    <div className="container">
      <h1>Traffic Light Control</h1>
      <div className="button-container">
        <button onClick={() => toggleLED('red')}>Red</button>
        <button onClick={() => toggleLED('green')}>Green</button>
        <button onClick={() => toggleLED('blue')}>Blue</button>
      </div>
      <div className="status">{status}</div>
    </div>
  );
};

export default TrafficLightControl;
