-- Registro y validación de pin

module ModeloUsuarios (Usuario(..), crearUsuario, validarPin) where

-- Definición de un usuario
data Usuario = Usuario {
    nombreUsuario :: String,
    pinUsuario    :: String
} deriving (Show)

-- Crea un nuevo usuario con su nombre y pin
crearUsuario :: String -> String -> Usuario
crearUsuario nombre pin = Usuario { nombreUsuario = nombre, pinUsuario = pin }

-- Valida si el pin ingresado es correcto para el usuario dado
validarPin :: Usuario -> String -> Bool
validarPin usuario pinIngresado = pinUsuario usuario == pinIngresado
