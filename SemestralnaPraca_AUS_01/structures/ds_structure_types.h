#pragma once

namespace structures {

	// Typy
	typedef unsigned char byte;

	// ADT sktruktur
	enum StructureADT {
		adtVECTOR,
		adtARRAY,
		adtLIST,
		adtQUEUE,
		adtSTACK,
		adtPRIORITY_QUEUE,
		adtTREE,
		adtGRAPH,
		adtTABLE,
		adtCount,
	};

	// ADS struktur
	enum StructureADS {
		adsVECTOR,
		adsARRAY,

		adsLIST_ARRAY,
		adsLIST_LINKED,
		adsLIST_DOUBLE_LINKED,
		adsLIST_CYCLICAL,

		adsQUEUE_ARRAY,
		adsQUEUE_LIST,

		adsSTACK_ARRAY,
		adsSTACK_LIST,

		adsPRIORITY_QUEUE_ARRAY_LIST_UNSORTED,
		adsPRIORITY_QUEUE_ARRAY_LIST_SORTED,
		adsPRIORITY_QUEUE_LINKED_LIST,
		adsPRIORITY_QUEUE_TWO_LISTS,
		adsPRIORITY_QUEUE_DOUBLE_LAYER,
		adsPRIORITY_QUEUE_HEAP,

		adsTREE_MULTI_WAY,
		adsTREE_K_WAY,
		adsTREE_BINARY,

		adsGRAPH_MATRIX,
		adsGRAPH_FORWARD_STAR,
		adsGRAPH_BI_STAR,

		adsTABLE_SEQUENCE_SORTED,
		adsTABLE_SEQUENCE_UNSORTED,
		adsTABLE_LINKED,
		adsTABLE_DIAMOND,
		adsTABLE_HASH,
		adsTABLE_BST,
		adsTABLE_TREAP,

		adsCount
	};

}