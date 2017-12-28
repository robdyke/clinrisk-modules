/* 
 * Copyright 2014 ClinRisk Ltd.
 * 
 * This file is part of QDiabetesAmpBlind (http://qdiabetes.org/amputation-blindness, http://svn.clinrisk.co.uk/opensource/qdiabetes).
 * 
 * QDiabetesAmpBlind is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * QDiabetesAmpBlind is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with QDiabetesAmpBlind.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Additional terms
 * 
 * The following disclaimer must be displayed alongside any risk score generated by this code.
 *   The initial version of this file, to be found at http://svn.clinrisk.co.uk/opensource/qdiabetes, faithfully implements QDiabetesAmpBlind.
 *   We have released this code under the GNU Affero General Public License to enable others to implement the algorithm faithfully.
 *   However, the nature of the GNU Affero General Public License is such that we cannot prevent, for example, someone accidentally 
 *   altering the coefficients, getting the inputs wrong, or just poor programming.
 *   We stress, therefore, that it is the responsibility of the end user to check that the source that they receive produces the same results as the original code posted at http://svn.clinrisk.co.uk/opensource/qdiabetes.
 *   Inaccurate implementations of risk scores can lead to wrong patients being given the wrong treatment.
 * 
 * This file has been auto-generated.
 * XML source: Q92_amputation_9_1.xml
 * STATA dta time stamp: 16 Jan 2015 13:01
 * This file was created on: Mon  9 Nov 2015 09:52:15 GMT
 */

#include <math.h>
#include <string.h>
#include <clinrisk/Q92_amputation_9_1.h>
#include <clinrisk/utils.h>

static double amputation_male_raw(
int age,int b_AF,int b_CCF,int b_pvd,int b_ra,int b_renal,int b_type1,int diabetes_years2,int ethrisk,double hba1c,double sbp,int smoke_cat,int surv,double town
)
{
	double survivor[16] = {
		0,
		0.999087810516357,
		0.998221695423126,
		0.997319757938385,
		0.996287703514099,
		0.995291650295258,
		0.994236648082733,
		0.993040680885315,
		0.991755008697510,
		0.990556299686432,
		0.989226996898651,
		0.987858831882477,
		0.986153125762939,
		0.984180271625519,
		0.982283711433411,
		0.980095505714417
	};

	/* The conditional arrays */

	double Iduration[5] = {
		0,
		0.5196280918906383000000000,
		0.7092759131461258100000000,
		0.9836654078077469200000000,
		1.2494014806613689000000000
	};
	double Iethrisk[10] = {
		0,
		0,
		-0.8737604738531864500000000,
		-0.9055506815436562600000000,
		-2.1106504986825172000000000,
		-0.8674116974111145700000000,
		-0.7145159834605158100000000,
		-0.9712949649571595000000000,
		-1.0464769530304270000000000,
		-0.4646174283658786000000000
	};
	double Ismoke[5] = {
		0,
		-0.0570648155410105050000000,
		0.2433437623567748200000000,
		0.1357761402487203100000000,
		0.2291797202954908900000000
	};

	/* Applying the fractional polynomial transforms */
	/* (which includes scaling)                      */

	double dhba1c = hba1c;
	dhba1c=dhba1c/100;
	double hba1c_2 = pow(dhba1c,2)*log(dhba1c);
	double hba1c_1 = pow(dhba1c,2);
	double dsbp = sbp;
	dsbp=dsbp/100;
	double sbp_1 = pow(dsbp,-2);
	double sbp_2 = pow(dsbp,.5);

	/* Centring the continuous variables */

	age = age - 59.462402343750000;
	hba1c_1 = hba1c_1 - 0.405204951763153;
	hba1c_2 = hba1c_2 - -0.183023437857628;
	sbp_1 = sbp_1 - 0.522531092166901;
	sbp_2 = sbp_2 - 1.176175117492676;
	town = town - 0.000000000000000;

	/* Start of Sum */
	double a=0;

	/* The conditional sums */

	a += Iduration[diabetes_years2];
	a += Iethrisk[ethrisk];
	a += Ismoke[smoke_cat];

	/* Sum from continuous values */

	a += age * 0.0175906378380952900000000;
	a += hba1c_1 * 1.7172943814562078000000000;
	a += hba1c_2 * -1.8807544914004244000000000;
	a += sbp_1 * 1.1836374661522289000000000;
	a += sbp_2 * 3.8125858354187407000000000;
	a += town * 0.0505398909001051260000000;

	/* Sum from boolean values */

	a += b_AF * 0.2341001055261638400000000;
	a += b_CCF * 0.2931583805343334100000000;
	a += b_pvd * 1.1501208857424827000000000;
	a += b_ra * 0.3327668158858001500000000;
	a += b_renal * 0.8175746261917235000000000;
	a += b_type1 * 0.2298386252428034100000000;

	/* Sum from interaction terms */


	/* Calculate the score itself */
	double score = 100.0 * (1 - pow(survivor[surv], exp(a)) );
	return score;
}

static int amputation_male_validation(
int age,int b_AF,int b_CCF,int b_pvd,int b_ra,int b_renal,int b_type1,int diabetes_years2,int ethrisk,double hba1c,double sbp,int smoke_cat,int surv,double town,char *errorBuf,int errorBufSize
)
{
	int ok=1;
	*errorBuf=0;
	if (!i_in_range(age,16,84)) {
		ok=0;
		strlcat(errorBuf,"error: age must be in range (16,84)\n",errorBufSize);
	}
	if (!is_boolean(b_AF)) {
		ok=0;
		strlcat(errorBuf,"error: b_AF must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_CCF)) {
		ok=0;
		strlcat(errorBuf,"error: b_CCF must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_pvd)) {
		ok=0;
		strlcat(errorBuf,"error: b_pvd must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_ra)) {
		ok=0;
		strlcat(errorBuf,"error: b_ra must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_renal)) {
		ok=0;
		strlcat(errorBuf,"error: b_renal must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_type1)) {
		ok=0;
		strlcat(errorBuf,"error: b_type1 must be in range (0,1)\n",errorBufSize);
	}
	if (!i_in_range(diabetes_years2,0,4)) {
		ok=0;
		strlcat(errorBuf,"error: diabetes_years2 must be in range (0,4)\n",errorBufSize);
	}
	if (!i_in_range(ethrisk,1,9)) {
		ok=0;
		strlcat(errorBuf,"error: ethrisk must be in range (1,9)\n",errorBufSize);
	}
	if (!d_in_range(hba1c,20,240)) {
		ok=0;
		strlcat(errorBuf,"error: hba1c must be in range (20,240)\n",errorBufSize);
	}
	if (!d_in_range(sbp,70,250)) {
		ok=0;
		strlcat(errorBuf,"error: sbp must be in range (70,250)\n",errorBufSize);
	}
	if (!i_in_range(smoke_cat,0,4)) {
		ok=0;
		strlcat(errorBuf,"error: smoke_cat must be in range (0,4)\n",errorBufSize);
	}
	if (!i_in_range(surv,1,10)) {
		ok=0;
		strlcat(errorBuf,"error: surv must be in range (1,10)\n",errorBufSize);
	}
	if (!d_in_range(town,-7,11)) {
		ok=0;
		strlcat(errorBuf,"error: town must be in range (-7,11)\n",errorBufSize);
	}
	return ok;
}

double amputation_male(
int age,int b_AF,int b_CCF,int b_pvd,int b_ra,int b_renal,int b_type1,int diabetes_years2,int ethrisk,double hba1c,double sbp,int smoke_cat,int surv,double town,int *error,char *errorBuf,int errorBufSize
)
{
	*error = 0;	int ok = amputation_male_validation(age,b_AF,b_CCF,b_pvd,b_ra,b_renal,b_type1,diabetes_years2,ethrisk,hba1c,sbp,smoke_cat,surv,town,errorBuf,errorBufSize);
	if(!ok) { 
		*error = 1;
		return 0.0;
	}
	return amputation_male_raw(age,b_AF,b_CCF,b_pvd,b_ra,b_renal,b_type1,diabetes_years2,ethrisk,hba1c,sbp,smoke_cat,surv,town);
}