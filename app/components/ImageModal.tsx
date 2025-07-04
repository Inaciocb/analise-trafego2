"use client";

import { useEffect } from "react";

export default function ImageModal({
  isOpen,
  onClose,
  src,
  alt,
  descricao,
}: {
  isOpen: boolean;
  onClose: () => void;
  src: string;
  alt: string;
  descricao?: string;
}) {
  useEffect(() => {
    const handleEsc = (e: KeyboardEvent) => {
      if (e.key === "Escape") onClose();
    };
    if (isOpen) {
      document.addEventListener("keydown", handleEsc);
    }
    return () => {
      document.removeEventListener("keydown", handleEsc);
    };
  }, [isOpen, onClose]);

  if (!isOpen) return null;

  return (
    <div
      className="fixed inset-0 z-50 flex items-center justify-center bg-black/80 backdrop-blur-sm transition-opacity"
      onClick={onClose}
    >
      <div
        className="max-w-4xl max-h-[90vh] p-2"
        onClick={(e) => e.stopPropagation()}
      >
        <img
          src={src}
          alt={alt}
          className="rounded-lg shadow-xl transition-transform duration-300 transform hover:scale-105 max-h-[80vh] w-auto mx-auto"
        />
        <p className="text-center text-sm text-gray-300 mt-2">{alt}</p>
        {descricao && (
          <p className="text-center text-xs text-gray-400 mt-1 italic px-4">{descricao}</p>
        )}
      </div>
    </div>
  );
}
