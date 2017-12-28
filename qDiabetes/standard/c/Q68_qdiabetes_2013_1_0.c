/* 
 * Copyright 2012 ClinRisk Ltd.
 * 
 * This file is part of QDiabetes-2013 (http://qdiabetes.org, http://svn.clinrisk.co.uk/opensource/qdiabetes).
 * 
 * QDiabetes-2013 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * QDiabetes-2013 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with QDiabetes-2013.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Additional terms
 * 
 * The following disclaimer must be displayed alongside any risk score generated by this code.
 *   The initial version of this file, to be found at http://svn.clinrisk.co.uk/opensource/qdiabetes, faithfully implements QDiabetes-2013.
 *   We have released this code under the GNU Lesser General Public License to enable others to implement the algorithm faithfully.
 *   However, the nature of the GNU Lesser General Public License is such that we cannot prevent, for example, someone altering the coefficients.
 *   We stress, therefore, that it is the responsibility of the end user to check that the source that they receive produces the same results as the original code posted at http://svn.clinrisk.co.uk/opensource/qdiabetes.
 *   Inaccurate implementations of risk scores can lead to wrong patients being given the wrong treatment.
 * 
 * This file has been auto-generated.
 * XML source: Q68_qdiabetes_2013_1_0.xml
 * STATA dta time stamp: 15 Feb 2013 11:36
 * This file was created on: Fri 15 Feb 2013 11:40:31 GMT
 */

#include <math.h>
#include <string.h>
#include <clinrisk/Q68_qdiabetes_2013_1_0.h>
#include <clinrisk/utils.h>

static double type2_female_raw(
int age,int b_corticosteroids,int b_cvd,int b_treatedhyp,double bmi,int ethrisk,int fh_diab,int smoke_cat,int surv,double town
)
{
	double survivor[16] = {
		0,
		0.998714804649353,
		0.997435748577118,
		0.996052920818329,
		0.994562506675720,
		0.992949724197388,
		0.991141080856323,
		0.989293158054352,
		0.987293541431427,
		0.985133886337280,
		0.982810735702515,
		0.980465650558472,
		0.978020071983337,
		0.975493073463440,
		0.972945988178253,
		0.970350146293640
	};

	/* The conditional arrays */

	double Iethrisk[10] = {
		0,
		0,
		1.2672136244963337000000000,
		1.4277605208830098000000000,
		1.8624060798103199000000000,
		1.2379988338989651000000000,
		0.4709034172907677900000000,
		0.3476400901703160500000000,
		1.1587283467731935000000000,
		0.7335499325010315100000000
	};
	double Ismoke[5] = {
		0,
		0.1012537024947505100000000,
		0.1915520564380613400000000,
		0.3091894136143333900000000,
		0.4646730392693820800000000
	};

	/* Applying the fractional polynomial transforms */
	/* (which includes scaling)                      */

	double dage = age;
	dage=dage/10;
	double age_1 = pow(dage,.5);
	double age_2 = pow(dage,3);
	double dbmi = bmi;
	dbmi=dbmi/10;
	double bmi_1 = dbmi;
	double bmi_2 = pow(dbmi,3);

	/* Centring the continuous variables */

	age_1 = age_1 - 2.135220289230347;
	age_2 = age_2 - 94.766799926757813;
	bmi_1 = bmi_1 - 2.549620866775513;
	bmi_2 = bmi_2 - 16.573980331420898;
	town = town - -0.224075347185135;

	/* Start of Sum */
	double a=0;

	/* The conditional sums */

	a += Iethrisk[ethrisk];
	a += Ismoke[smoke_cat];

	/* Sum from continuous values */

	a += age_1 * 4.3848331212989669000000000;
	a += age_2 * -0.0049763964406541149000000;
	a += bmi_1 * 3.3753336326064329000000000;
	a += bmi_2 * -0.0631628488667318330000000;
	a += town * 0.0432726992998635970000000;

	/* Sum from boolean values */

	a += b_corticosteroids * 0.2681990966241487000000000;
	a += b_cvd * 0.3596176830984252900000000;
	a += b_treatedhyp * 0.5314598436974725700000000;
	a += fh_diab * 0.7315358845837640600000000;

	/* Sum from interaction terms */

	a += age_1 * bmi_1 * 1.3037832873997990000000000;
	a += age_1 * bmi_2 * -0.0708293717769046120000000;
	a += age_1 * fh_diab * -0.7968266815834251800000000;
	a += age_2 * bmi_1 * -0.0067725323761278549000000;
	a += age_2 * bmi_2 * 0.0002374980728666116700000;
	a += age_2 * fh_diab * 0.0017048228889394394000000;

	/* Calculate the score itself */
	double score = 100.0 * (1 - pow(survivor[surv], exp(a)) );
	return score;
}

static int type2_female_validation(
int age,int b_corticosteroids,int b_cvd,int b_treatedhyp,double bmi,int ethrisk,int fh_diab,int smoke_cat,int surv,double town,char *errorBuf,int errorBufSize
)
{
	int ok=1;
	*errorBuf=0;
	if (!i_in_range(age,25,84)) {
		ok=0;
		strlcat(errorBuf,"error: age must be in range (25,84)\n",errorBufSize);
	}
	if (!is_boolean(b_corticosteroids)) {
		ok=0;
		strlcat(errorBuf,"error: b_corticosteroids must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_cvd)) {
		ok=0;
		strlcat(errorBuf,"error: b_cvd must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_treatedhyp)) {
		ok=0;
		strlcat(errorBuf,"error: b_treatedhyp must be in range (0,1)\n",errorBufSize);
	}
	if (!d_in_range(bmi,20,40)) {
		ok=0;
		strlcat(errorBuf,"error: bmi must be in range (20,40)\n",errorBufSize);
	}
	if (!i_in_range(ethrisk,1,9)) {
		ok=0;
		strlcat(errorBuf,"error: ethrisk must be in range (1,9)\n",errorBufSize);
	}
	if (!is_boolean(fh_diab)) {
		ok=0;
		strlcat(errorBuf,"error: fh_diab must be in range (0,1)\n",errorBufSize);
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

double type2_female(
int age,int b_corticosteroids,int b_cvd,int b_treatedhyp,double bmi,int ethrisk,int fh_diab,int smoke_cat,int surv,double town,int *error,char *errorBuf,int errorBufSize
)
{
	*error = 0;	int ok = type2_female_validation(age,b_corticosteroids,b_cvd,b_treatedhyp,bmi,ethrisk,fh_diab,smoke_cat,surv,town,errorBuf,errorBufSize);
	if(!ok) { 
		*error = 1;
		return 0.0;
	}
	return type2_female_raw(age,b_corticosteroids,b_cvd,b_treatedhyp,bmi,ethrisk,fh_diab,smoke_cat,surv,town);
}
