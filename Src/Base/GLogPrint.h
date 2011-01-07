#pragma once

void GLogPrintMatrix44(const M3DMatrix44f M) {
	DLOG(INFO) << "[" << M[0] << ", " << M[1] << ", " << M[2] << ", " << M[3] << endl;
	DLOG(INFO) << " " << M[4] << ", " << M[5] << ", " << M[6] << ", " << M[7] << endl;
	DLOG(INFO) << " " << M[8] << ", " << M[9] << ", " << M[10] << ", " << M[11] << endl;
	DLOG(INFO) << " " << M[12] << ", " << M[13] << ", " << M[14] << ", " << M[15] << "]" << endl;
}

void GLogPrintVector3(const float* V) {
	DLOG(INFO) << "(" << V[0] << ", " << V[1] << ", " << V[2] << ")" << endl;
}
