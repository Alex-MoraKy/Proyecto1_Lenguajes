-- La vaina de cifrar

module Cifrado (cifrarConXor) where

import Data.Bits (xor)
import Data.Char (ord, chr)

-- Cifra o descifra un texto usando una clave con XOR
cifrarConXor :: String -> String -> String
cifrarConXor clave texto = zipWith (\c k -> chr (ord c `xor` ord k)) texto (cycle clave)
