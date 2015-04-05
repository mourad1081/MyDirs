IF [%1]==[] goto :fin
IF [%2]==[] goto :fin
%2
attrib +h +s +a %1
:fin