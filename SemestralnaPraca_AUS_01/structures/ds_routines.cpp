#include <stdexcept>

#include "ds_routines.h"

namespace structures {
	DSRoutines::DSRoutines()
	{
	}

	StructureADT DSRoutines::convertADStoADT(const StructureADS& ads)
	{
		switch (ads)
		{
		case adsVECTOR:
			return adtVECTOR;

		case adsARRAY:
			return adtARRAY;

		case adsLIST_ARRAY:
		case adsLIST_LINKED:
		case adsLIST_DOUBLE_LINKED:
		case adsLIST_CYCLICAL:
			return adtLIST;

		case adsQUEUE_ARRAY:
		case adsQUEUE_LIST:
			return adtQUEUE;

		case adsSTACK_ARRAY:
		case adsSTACK_LIST:
			return adtSTACK;

		case adsPRIORITY_QUEUE_ARRAY_LIST_SORTED:
		case adsPRIORITY_QUEUE_ARRAY_LIST_UNSORTED:
		case adsPRIORITY_QUEUE_LINKED_LIST:
		case adsPRIORITY_QUEUE_TWO_LISTS:
		case adsPRIORITY_QUEUE_DOUBLE_LAYER:
		case adsPRIORITY_QUEUE_HEAP:
			return adtPRIORITY_QUEUE;

		case adsTREE_MULTI_WAY:
		case adsTREE_K_WAY:
		case adsTREE_BINARY:
			return adtTREE;

		case adsGRAPH_MATRIX:
		case adsGRAPH_FORWARD_STAR:
		case adsGRAPH_BI_STAR:
			return adtGRAPH;

		case adsTABLE_SEQUENCE_SORTED:
		case adsTABLE_SEQUENCE_UNSORTED:
		case adsTABLE_LINKED:
		case adsTABLE_DIAMOND:
		case adsTABLE_HASH:
		case adsTABLE_BST:
		case adsTABLE_TREAP:
			return adtTABLE;

		default:
			throw std::invalid_argument("Cannot convert ADS to ADT");
		}
	}

	bool DSRoutines::rangeCheck(const int index, const size_t size)
	{
		return DSRoutines::rangeCheck(index, 0, size);
	}

	bool DSRoutines::rangeCheck(const int index, const int baseIndex, const size_t size)
	{
		return index >= baseIndex && index < baseIndex + static_cast<int>(size);
	}

	void DSRoutines::rangeCheckExcept(const int index, const size_t size, const std::string exceptionMessage)
	{
		DSRoutines::rangeCheckExcept(index, 0, size, exceptionMessage);
	}

	void DSRoutines::rangeCheckExcept(const int index, const int baseIndex, const size_t size, const std::string exceptionMessage)
	{
		if (!DSRoutines::rangeCheck(index, baseIndex, size))
		{
			throw std::out_of_range(exceptionMessage);
		}
	}

	double DSRoutines::getInfinity()
	{
		return std::numeric_limits<double>::infinity();
	}
}