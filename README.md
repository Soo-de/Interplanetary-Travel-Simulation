# Interplanetary Travel Simulation

A modular, object-oriented simulation of interplanetary spacecraft, aging passengers, and dynamic planetary populations — implemented in both Java and C to compare OOP and procedural approaches.

---

## 🚀 Simulation Rules & Key Features

### Project Overview

This simulation models the interplanetary travel of spaceships carrying passengers between planets. The program tracks passengers' lifespans and manages spaceship statuses based on real-time events and conditions.

Notably, the project was implemented both in Java using classic OOP principles and in C by simulating OOP concepts through modular and structured programming techniques, demonstrating how object-oriented design can be approximated in C.

---

### ⚙️ Core Simulation Rules

- **Departure & Travel:**  
  Spaceships depart exactly at their scheduled departure times. They travel towards their target planet, and their arrival time depends on the remaining distance.

- **Passenger Lifespan & Spaceship Status:**  
  Each passenger ages as time passes. If all passengers on a spaceship die, the spaceship is immediately destroyed — regardless of its current status (in transit, arrived, or waiting).

- **Spaceship Lifecycle:**  
  Spaceships remain active in the simulation until they are either destroyed or have successfully arrived at their destination.

---

### 🧩 Additional Rules in C Implementation

- **Planet-Type Affected Aging:**  
  In the C version, passengers’ aging speed varies according to the planet type where their spaceship is currently located. Different planet types (e.g., gas giants, rocky planets) influence how quickly passengers age, adding complexity and realism to the simulation.

- **OOP Simulation in C:**  
  The C implementation uses modular design patterns to mimic object-oriented programming concepts such as encapsulation and modularity, providing a clear example of applying OOP principles in a procedural language.

---

### 🎯 Key Focus Areas

- Time-based event management (scheduled departures and travel progress).  
- Dynamic population tracking based on passenger survival.  
- Modular simulation design adaptable between Java’s OOP and C’s structured approach.  
- Implementation of varying aging rates linked to planetary environments (C version).  
- Demonstrating OOP principles through C language modularity and abstractions.

---

### 📝 Note

This project was completed as part of the Programming Languages and Principles course during my second year at Sakarya University.
