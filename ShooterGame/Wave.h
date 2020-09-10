#pragma once

// ŠeWave
enum class Wave
{
	FirstWave,
	SecondWave,
	ThirdWave,
	Max
};

static Wave begin(Wave)
{
	return Wave::FirstWave;
}

static Wave end(Wave)
{
	return Wave::Max;
}

static Wave operator++(Wave& wave)
{
	return (wave = (Wave)(std::underlying_type<Wave>::type(wave) + 1));
}

static Wave operator+(Wave wave,int n)
{
	return (Wave)(int(wave) + n);
}

static Wave operator-(Wave wave, int n)
{
	return (Wave)(int(wave) - n);
}

static Wave operator*(Wave& wave)
{
	return wave;
}


