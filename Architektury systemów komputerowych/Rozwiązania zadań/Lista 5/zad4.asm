        PUSH Y
        POP W       ; Tymczasowo W = Y
        PUSH X
        SUB Y
        JMPGTZ yltx ; Jump if MIN(X,Y) = Y
xlty:   PUSH X
        POP W       ; MIN(X,Y) = X
yltx:   PUSH Z
        SUB W
        JMPGTZ end
zltw:   PUSH Z
        POP W
end:

