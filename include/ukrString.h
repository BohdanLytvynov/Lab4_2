#ifndef UKRSTRING_H

#define UKRSTRING_H

#include<string>
#include<iostream>
#include<fstream>
#include"smart_alloc.h"
#include<vector>

namespace strings
{	
	struct ukrString
	{
		using Word = std::vector<char>;

		using wordSet = std::vector<Word>;

#pragma region Interface functions
		/// <summary>
		/// Returns the length of the string
		/// </summary>
		/// <returns>Size of the string</returns>
		size_t getLength() const;

		/// <summary>
		/// Creates ukrString from c-string
		/// </summary>
		/// <param name="src">Pointer to c-string</param>
		/// <param name="length">Size of the c-string</param>
		void from_char_ptr(char* src, size_t length);

		/// <summary>
		/// Create ukrString from the simple std::string
		/// </summary>
		/// <param name="str">Source string</param>
		void from_string(const std::string& str);

		/// <summary>
		/// Returns the pointer to the first char of the ukrString
		/// </summary>
		/// <returns>Pointer to the first char of the ukrString</returns>
		char* get_chars();

		/// <summary>
		/// Convert current ukrString to std::string
		/// </summary>
		/// <returns>std::string</returns>
		std::string to_string() const;

		/// <summary>
		/// Disable symbol offset. Use it only when ukrString is used for input
		/// </summary>
		void use_for_input();

		/// <summary>
		/// Enable symbol offset. 
		/// </summary>
		void not_for_input();

		/// <summary>
		/// Indicates wether symbol offset is enabled
		/// </summary>
		/// <returns>Bool, wether symbol offset is enabled</returns>
		bool is_used_for_input() const;

#pragma endregion

#pragma region public static Functions
		/// <summary>
		/// Function that performs symbol offset
		/// </summary>
		/// <param name="str">input string</param>
		/// <returns>A c-string</returns>
		static char Ukr(char str);

		/// <summary>
		/// Creates a new ukrString. Writes symbols from src to dest.
		/// </summary>
		/// <param name="src">Source for copy.</param>
		/// <param name="dest">Destination for copy.</param>
		/// <param name="start">Start index for copying</param>
		/// <param name="end">End index for copying.</param>
		static void ukrStrCopy(ukrString& src, ukrString dest, int start, int end);

		/// <summary>
		/// Function that gets the input from console
		/// </summary>
		/// <param name="is">Input stream object</param>
		/// <param name="output">Input stream object</param>
		/// <returns>The same Input stream object</returns>
		static std::istream& getLine(std::istream& is, ukrString& output);

		/// <summary>
		/// Function that gets line from the file 
		/// </summary>
		/// <param name="ifs">Input file stream object</param>
		/// <param name="output">ukrString that was get from the file</param>
		/// <returns></returns>
		static std::ifstream& getLine(std::ifstream& ifs, ukrString& output);

#pragma region ukrString extension functions 

		/// <summary>
		/// Function that excepts ukrString object and splits it to the std::vector<std::vector<char>>
		/// </summary>
		/// <param name="str">ukrString input string</param>
		/// <param name="word_Set">output</param>
		/// <param name="delim">Array of chars</param>
		static void Split(strings::ukrString& str, wordSet& word_Set,
			const char delim[]);

#pragma endregion


#pragma endregion

#pragma region Ctors
		/// <summary>
		/// Empty ctor
		/// </summary>
		ukrString();

		/// <summary>
		/// Convert c-string to ukrString
		/// </summary>
		/// <param name="str">Source c-string</param>
		/// <param name="length">Length of the c-string</param>
		ukrString(char* str, size_t length);

		/// <summary>
		/// Converts c-string to ukrString
		/// </summary>
		/// <param name="str">Source c-string</param>
		explicit ukrString(const char* str);

		/// <summary>
		/// Converts std::string to ukrString
		/// </summary>
		/// <param name="str">Source std::string</param>
		explicit ukrString(const std::string& str);

		/// <summary>
		/// Copy ctor
		/// </summary>
		/// <param name="other">Source for copy</param>
		ukrString(const ukrString& other);

		/// <summary>
		/// Convert std::vector<char> to the ukrString
		/// </summary>
		/// <param name="v">Input parametr</param>
		explicit ukrString(std::vector<char>& v);

		/// <summary>
		/// Convert int number to ukrString
		/// </summary>
		/// <param name="number">Input number for convertion</param>
		explicit ukrString(int number);

		/// <summary>
		/// Convert float number to ukrString 
		/// </summary>
		/// <param name="number">Input number for convertion</param>
		explicit ukrString(float number);

		/// <summary>
		/// Convert doube number to ukrString
		/// </summary>
		/// <param name="number">Input number for convertion</param>
		explicit ukrString(double number);

		/// <summary>
		/// Converter for custom type
		/// </summary>
		/// <typeparam name="Tin">Type to convert to</typeparam>
		/// <param name="obj">Input object for convertion</param>
		/// <param name="strFiller">Function pointer that provides logic for convertion object of Tin type to ukrString</param>
		template<class Tin>
		explicit ukrString(const Tin& obj, std::function<void(Tin& obj, ukrString& cur)> strFiller)
		{
			if (!strFiller) throw std::runtime_error("strFiller parametr is not set!");

			strFiller(obj, this);
		}

		
		
#pragma endregion

#pragma region Operators
		/// <summary>
		/// Assignment operator
		/// </summary>
		/// <param name="other">Source ukrString</param>
		/// <returns>ukrString</returns>
		ukrString& operator = (const ukrString& other);

		/// <summary>
		/// Overloaded assignment operator for c-string
		/// </summary>
		/// <param name="cstr">Source c-string</param>
		/// <returns>ukrString</returns>
		ukrString& operator = (const char cstr[]);
		
		/// <summary>
		/// Output operator to the console
		/// </summary>
		/// <param name="os">Output stream</param>
		/// <param name="string">ukrString</param>
		/// <returns>Output stream</returns>
		friend std::ostream& operator << (std::ostream& os, ukrString& string)
		{
			size_t length = string.getLength();

			for (size_t i = 0; i < length; i++)
			{
				if (string.m_use_for_input)
					os << string[i];
				else
					os << Ukr(string[i]);
			}

			return os;
		}

		/// <summary>
		/// Overloaded output operator for constant ukrStrings
		/// </summary>
		/// <param name="os">Output stream</param>
		/// <param name="string">ukrString</param>
		/// <returns>Output stream</returns>
		friend std::ostream& operator << (std::ostream& os, const ukrString& string)
		{
			size_t length = string.getLength();

			for (size_t i = 0; i < length; i++)
			{
				if (string.m_use_for_input)
					os << string[i];
				else
					os << Ukr(string[i]);
			}

			return os;
		}

		/// <summary>
		/// Input operator for the console
		/// </summary>
		/// <param name="is">Input stream</param>
		/// <param name="string">ukrString</param>
		/// <returns>Input stream</returns>
		friend std::istream& operator >> (std::istream& is, ukrString& string)
		{
			std::string str;

			is >> str;

			string.from_char_ptr(str._Unchecked_begin(), str.length());

			return is;
		}

		/////////////////////Filestream operators

		/// <summary>
		/// Writes ukrString to some output file stream object
		/// </summary>
		/// <param name="ofs">output file stream object</param>
		/// <param name="str">ukrString</param>
		/// <returns>output file stream object</returns>
		friend std::ofstream& operator <<(std::ofstream& ofs, const ukrString& str) 
		{
			size_t size = str.getLength();

			for (size_t i = 0; i < size; i++)
			{
				ofs << str[i];
			}

			return ofs;
		}

		/// <summary>
		/// Writes ukrString to some output file stream object
		/// </summary>
		/// <param name="ofs">output file stream object</param>
		/// <param name="str">ukrString</param>
		/// <returns>output file stream object</returns>
		friend std::ofstream& operator <<(std::ofstream& ofs, ukrString& str)
		{
			size_t size = str.getLength();

			for (size_t i = 0; i < size; i++)
			{
				ofs << str[i];
			}

			return ofs;
		}

		/// <summary>
		/// Converts ukrString to the std::string
		/// </summary>
		operator std::string() const;

		/// <summary>
		/// Indexer, allows to get read write access to the symbol of the ukrString
		/// </summary>
		/// <param name="index">Index of the symbol</param>
		/// <returns>Reference to the symbol</returns>
		char& operator [] (int index);

		/// <summary>
		/// Overloaded indexer. Allows to read symbol of the ukrString
		/// </summary>
		/// <param name="index">Index of the symbol</param>
		/// <returns>Constant reference to the symbol</returns>
		const char& operator [] (int index) const;
		/// <summary>
		/// Operator for ukrString concatenation
		/// </summary>
		/// <param name="other">ukrString for concatenation</param>
		/// <returns>New ukrString after concatenation</returns>
		ukrString operator + (const ukrString& other) const;

		/// <summary>
		/// Operator for ukrString concatenation
		/// </summary>
		/// <param name="other">ukrString for concatenation</param>
		void operator += (const ukrString& other);

		/// <summary>
		/// Equality operator
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool operator == (const ukrString& other);

		/// <summary>
		/// Unequality operator
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool operator != (const ukrString& other);


#pragma endregion


#pragma region Destructor
		//Finalizer. Releases dynamic resources according to RAII paradigm
		~ukrString();
#pragma endregion

	private:

#pragma region Fields

		allocator::smart_allocator<char> m_chars;//Stores chars 		

		bool m_use_for_input;//Indicates wether symbol offset is enabled

#pragma endregion

#pragma region Private Static Functions
		/// <summary>
		/// Compares current character with each character in the delim array
		/// </summary>
		/// <param name="current">Current character</param>
		/// <param name="delim">Array of deliminators</param>
		/// <returns>true if current character equal to the character in delim array</returns>
		static bool Compare(char current, const char delim[]);		

#pragma endregion


	};


}

#endif // !UKRSTRING_H
