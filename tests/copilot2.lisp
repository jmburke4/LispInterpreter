(defun reverse-list (lst)
  "Reverses the elements of a list."
  (if (null lst)
      nil
      (append (reverse-list (cdr lst)) (list (car lst)))))

;; Example usage
(print (reverse-list '(1 2 3 4 5)))
