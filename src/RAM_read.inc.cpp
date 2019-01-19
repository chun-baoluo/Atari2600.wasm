// CXM0P
case 0x00: {
	return this->map[0x30];
	break;
}
// CXM1P
case 0x01: {
	return this->map[0x31];
	break;
}
// CXP0FB
case 0x02: {
    return this->map[0x32];
    break;
}
// INSTAT
case 0x285: {
	this->map[0x285] = this->map[0x285] & 0xBF;
	break;
}