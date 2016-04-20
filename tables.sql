CREATE TABLE Profiles(
    PNo   INTEGER PRIMARY KEY,
    Name  Text
); 

CREATE TABLE Bones(
    PNo    INTEGER,
    BNo    INTEGER,
    Left   Text,
    Right  Text,
    Length Text,
    Extra  Text,
    PRIMARY KEY (PNo, BNo)
); 