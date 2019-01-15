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