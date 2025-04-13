# finalProjectDE3
Sistema embebido para el control digital de un motor paso a paso o BLDC con interfaz de usuario en LCD, implementado con Raspberry Pi Pico.

# PicoMotion

## 📘 Descripción general

PicoMotion es un proyecto académico desarrollado como parte del curso de **Electrónica Digital III**, cuyo objetivo es diseñar un sistema embebido funcional que permita el control completo de un motor eléctrico desde una interfaz digital intuitiva. Todo el sistema corre sobre la plataforma **Raspberry Pi Pico**, y permite seleccionar velocidad, dirección de giro y tipo de motor (stepper o BLDC) de forma interactiva.

--- 

## ⚙️ Funcionalidades principales

- Selección de dirección de giro (horario / antihorario)
- Control de velocidad (lenta / media / rápida)
- Encendido y apagado del motor desde la interfaz
- Interfaz visual en pantalla LCD 16x2 (modo texto)
- Navegación por menú mediante botones o encoder rotatorio
- Visualización en tiempo real de:
  - Dirección
  - Velocidad
  - Estado del motor
  - Tipo de motor seleccionado

---
## 🧪 Escenario de pruebas

- Verificación funcional de cada parámetro configurable (dirección, velocidad, encendido)
- Evaluación de respuesta en tiempo real (≤ 200 ms)
- Prueba de estabilidad operativa continua por mínimo 2 horas
- Validación visual en pantalla LCD
- Testeo de consumo reducido cuando el motor está inactivo

---
## 📝 Requisitos funcionales

1. Control digital de dirección y velocidad del motor
2. Visualización clara del estado en la pantalla LCD
3. Control de encendido/apagado desde la interfaz
4. Menú interactivo operado mediante botones/encoder
5. Modularidad del código en C con uso del SDK oficial
6. Preparado para soporte de motores paso a paso o BLDC

---
## 📋 Requisitos no funcionales

- Tiempo de respuesta máximo: **200 ms**
- Interfaz amigable e intuitiva
- Código organizado en módulos independientes
- Estabilidad operativa mínima: **2 horas continuas**
- Ahorro energético cuando el motor está apagado
- Compatible con futuras expansiones (UART, Bluetooth)

---
## 💰 Presupuesto

Ver archivo adjunto: `Presupuesto_PicoMotion.csv`
**Costo estimado total del proyecto:** ≈ $116,000 COP (USD ~$30)

---

## Autor
Proyecto realizado por Daniel Ovany Mesa López  

