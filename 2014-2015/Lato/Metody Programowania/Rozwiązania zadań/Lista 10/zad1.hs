import Data.List
import Data.Char
nat :: [(Integer,Integer)]
nat = [(y,x-y)|x<-[0..], y <-[0..x]]
                                  --           XXXXX
